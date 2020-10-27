#include "communicate.h"

  #ifdef COMM_REMOTE
    
  #endif

struct Data_TX_t data_tx;
struct Data_RX_t data_rx;
uint8_t rx_buf = 0; 

void COMM_init(void)
{
  HAL_UART_Receive_IT(&comm_huart,data_rx.rx,sizeof(data_rx.rx));
  data_tx.start_flag = START_FLAG;
  data_tx.end_flag = END_FLAG;
  #ifdef COMM_REMOTE  
    data_tx.switch_flag = REMOTE_FLAG;
  #endif
}

void COMM_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &comm_huart)
	{
		HAL_UART_Receive_IT(&comm_huart,&rx_buf,1);
		COMM_ReceiveHandle();
	}
}

void COMM_ReceiveHandle(void)
{
    static int data_count = 0;
    data_rx.rx[data_count] = rx_buf;
    data_count++;
    if(data_rx.rx[0] != START_FLAG)
    {
        data_count = 0;
        return;
    }
    if(data_count < COMM_LEN) return;
    if(data_rx.rx[COMM_LEN - 1] != END_FLAG)
    {
        data_count = 0;
        return;
    }  
		//data_rx.rx  already has correct data inside 
    #ifdef COMM_REMOTE
    if(data_rx.rx[COMM_LEN - 2] == REMOTE_FLAG)
    {
        data_rx.channel[0]  = (uint16_t) ((data_rx.rx[1]    |data_rx.rx[2] <<8)                     & 0x07FF);
        data_rx.channel[1]  = (uint16_t) ((data_rx.rx[2]>>3 |data_rx.rx[3] <<5)                     & 0x07FF);
        data_rx.channel[2]  = (uint16_t) ((data_rx.rx[3]>>6 |data_rx.rx[4] <<2 |data_rx.rx[5]<<10)  & 0x07FF);
        data_rx.channel[3]  = (uint16_t) ((data_rx.rx[5]>>1 |data_rx.rx[6] <<7)                     & 0x07FF);
        data_rx.channel[4]  = (uint16_t) ((data_rx.rx[6]>>4 |data_rx.rx[7] <<4)                     & 0x07FF);
        data_rx.channel[5]  = (uint16_t) ((data_rx.rx[7]>>7 |data_rx.rx[8] <<1 |data_rx.rx[9]<<9)   & 0x07FF);
        data_rx.channel[6]  = (uint16_t) ((data_rx.rx[9]>>2 |data_rx.rx[10]<<6)                     & 0x07FF);
        data_rx.channel[7]  = (uint16_t) ((data_rx.rx[10]>>5|data_rx.rx[11]<<3)                     & 0x07FF);
    }
    #endif
}

	
void COMM_TramsmitHandle(void)
{
    #ifdef COMM_REMOTE
    data_tx.tx[0] = START_FLAG;
    data_tx.tx[1] = (uint8_t) ((data_tx.channel[0] & 0x07FF));
		data_tx.tx[2] = (uint8_t) ((data_tx.channel[0] & 0x07FF)>>8 | (data_tx.channel[1] & 0x07FF)<<3);
		data_tx.tx[3] = (uint8_t) ((data_tx.channel[1] & 0x07FF)>>5 | (data_tx.channel[2] & 0x07FF)<<6);
		data_tx.tx[4] = (uint8_t) ((data_tx.channel[2] & 0x07FF)>>2);
		data_tx.tx[5] = (uint8_t) ((data_tx.channel[2] & 0x07FF)>>10 | (data_tx.channel[3] & 0x07FF)<<1);
		data_tx.tx[6] = (uint8_t) ((data_tx.channel[3] & 0x07FF)>>7 | (data_tx.channel[4] & 0x07FF)<<4);
		data_tx.tx[7] = (uint8_t) ((data_tx.channel[4] & 0x07FF)>>4 | (data_tx.channel[5] & 0x07FF)<<7);
		data_tx.tx[8] = (uint8_t) ((data_tx.channel[5] & 0x07FF)>>1);
		data_tx.tx[9] = (uint8_t) ((data_tx.channel[5] & 0x07FF)>>9 | (data_tx.channel[6] & 0x07FF)<<2);
		data_tx.tx[10] = (uint8_t) ((data_tx.channel[6] & 0x07FF)>>6 | (data_tx.channel[7] & 0x07FF)<<5);
		data_tx.tx[11] = (uint8_t) ((data_tx.channel[7] & 0x07FF)>>3);    
    data_tx.tx[12] = REMOTE_FLAG;
    data_tx.tx[13] = END_FLAG;
    #endif
    //HAL_UART_Transmit_DMA(&comm_huart,data_tx.tx,sizeof(data_tx.tx));
	  //DMA tramsmit is useless now 
	  HAL_UART_Transmit_IT(&comm_huart,data_tx.tx,sizeof(data_tx.tx));
}

void Remote_init(void)
{
	__HAL_UART_ENABLE_IT(&comm_huart, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&comm_huart, data_rx.rx, sizeof(data_rx.rx));	
}

void UART_IDLE_Callback(UART_HandleTypeDef *huart)
{
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))      //????�???????????????
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);                 //???IDLE?????
		USART1->SR;                                       //???SR?????
		USART1->DR;                                       //???DR?????
		//__HAL_DMA_CLEAR_FLAG(huart, DMA_FLAG_TCIF2_6);    //???DMA???????????
		HAL_UART_DMAStop(huart);
		if(__HAL_DMA_GET_COUNTER(huart->hdmarx) == 0)     //????????????18
		{
//			RemoteData();
		}
		HAL_UART_Receive_DMA(&comm_huart, data_rx.rx, sizeof(data_rx.rx));		     
	}	
}


