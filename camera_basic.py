import cv2
# import numpy as np
print("opencv imported")

# This is a great test for git
# 我可以好好试一下
# 今天再试一下，规范一下一个工程同时推送到gitee和github的配置

# 今天是树莓派的测试
# 试一下git pull和git fetch的区别，再试一下？？？

frame_width = 640
frame_height = 480
cap = cv2.VideoCapture(0)  # 0号摄像头是默认摄像头
cap.set(3, frame_width)  # id3是设置画面宽度
cap.set(4, frame_height)
cap.set(10, 130)  # 设置亮度

while True:
    success, img = cap.read()
    cv2.imshow("video", img)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
