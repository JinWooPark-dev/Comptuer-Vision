# 프로젝트 계획 이유
## - 해당 프로젝트는 컴퓨터 비전에 대해 개인적인 학습에 목적이 있음
## - Computer-Vision에 관한 여러가지 기능 구현
# 개발 환경
## - Visual studio express 2012
## - openCV 라이브러리

# 내용
## 1. Filtering
###  1-1. Box Filter & Gaussian filter & Separable Kernel
| Origin Image| Box Filter image | Gaussian Filter Image | Separable Kernal Image|
| ------------ | ------------- | ------------- | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97958096-e7e70b80-1def-11eb-83fe-c280c79e2dcf.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97959153-0d751480-1df2-11eb-97c8-c2764df7983d.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97959208-2d0c3d00-1df2-11eb-9288-4f705bafdc46.jpg" width="270px" height="191px"/></p>|

### 1-2. Salt_Papper image & filter the image using median filter
| Salt_Papper Image| after median image |
| ------------ | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97960652-35b24280-1df5-11eb-989b-1676d6376fd6.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97960758-63978700-1df5-11eb-894a-725590c98a1e.jpg" width="270px" height="191px"/></p>|
## 2. Sharpening
| Origin Image| Sharpening image |
| ------------ | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97959815-7c06a200-1df3-11eb-8706-637abd62c681.jpg" width="270px" height="191px"/></p>|
## 3. Edge
### 3-1. PrewittFilter image
| Origin Image| PrewittFilter_X image |PrewittFilter_Y image |
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97961518-d05f5100-1df6-11eb-9c20-62ac0cb48e8e.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97961578-ef5de300-1df6-11eb-9640-8b8a03392b09.jpg" width="270px" height="191px"/></p>|
### 3-2. Robertes Image
| Origin Image| Robertes_X image |Robertes_Y image |
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97962620-ed951f00-1df8-11eb-8d0d-6283d9edab5f.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97962643-fab20e00-1df8-11eb-9a59-83df15913099.jpg" width="270px" height="191px"/></p>|
### 3-3. Sobel Filter image & Magnitude sobel Image & NonMaximum suppresion Image
| Origin Image| SobelFilter_X image |SobelFilter_Y image |Magnitude sobel image |NonMaximum suppresion image |
| ------------ | ------------- |------------- | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97961766-3cda5000-1df7-11eb-8f15-faf28846e43d.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97961800-49f73f00-1df7-11eb-9890-1bf5c41af171.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97962339-47491980-1df8-11eb-9ca7-5e51c8bd3f23.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97962354-529c4500-1df8-11eb-8bdd-f5e8773665c8.jpg" width="270px" height="191px"/></p>|

### 3-4. hysteresis threshold & canny edge image
| Hysteresis threshold low Image| Hysteresis threshold high Image |Canny edge image |
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97963070-c428c300-1df9-11eb-9677-e5c6b1262595.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97963076-c5f28680-1df9-11eb-85e7-a8c96a981d47.jpg" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97963084-c854e080-1df9-11eb-9fa0-cf941c64f40b.jpg" width="270px" height="191px"/></p>|
## 4. Corner detection
| Origin Image| Harris corner image |
| ------------ | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97957678-0a2c5980-1def-11eb-8022-83685b88ec60.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97963244-1a960180-1dfa-11eb-8239-49a875033865.jpg" width="270px" height="191px"/></p>|
## 5. Clustering
| before clustering Image| after clustering image |
| ------------ | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97963473-8c6e4b00-1dfa-11eb-82e8-d4f8be112398.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97963530-ab6cdd00-1dfa-11eb-8e7e-6f4172ce6964.jpg" width="270px" height="191px"/></p>|
## 6. Segmentation
| Origin Image| Image segmentation image | Image segmentation using color space Image | Image segmentation using Meanshift Image|
| ------------ | ------------- | ------------- | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97963889-3221ba00-1dfb-11eb-999a-8f15702c4d5d.jpg" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97963905-36e66e00-1dfb-11eb-83c7-5d65e11d69de.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97963911-3b128b80-1dfb-11eb-8be1-2488dfdf11fd.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97963916-3e0d7c00-1dfb-11eb-8a07-80770b2bfdd1.png" width="270px" height="191px"/></p>|
## 7. Optical Flow
| before Image| after image | Result image|
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97964387-06eb9a80-1dfc-11eb-8af1-c03a6e044ece.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97964398-0bb04e80-1dfc-11eb-9439-ad541db67957.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97964542-4619eb80-1dfc-11eb-960c-6d5fc10c43e0.PNG" width="270px" height="191px"/></p>|
## 8. Line Fitting
| line Image| line fitting image | line fitting using ransac image|
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97965136-3f3fa880-1dfd-11eb-93e2-7f3b115c61a1.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97965143-41a20280-1dfd-11eb-9bab-2ab6c0a77b1c.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97965145-42d32f80-1dfd-11eb-8b6e-21f5222dc756.png" width="270px" height="191px"/></p>|
## 9. Line Detection
| Origin Image| line Detection Using HoughTransform image |
| ------------ | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97965408-a8bfb700-1dfd-11eb-8609-bd2f35d61ba7.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97965430-b07f5b80-1dfd-11eb-9eec-ed4c3ab615e4.png" width="270px" height="191px"/></p>|
## 10. Affine Transform
| monalisa Image| frame image | Affine image|
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97965573-efadac80-1dfd-11eb-8806-ecd3e2c88331.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97965583-f4726080-1dfd-11eb-9828-a66ca201a2b1.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97965592-f76d5100-1dfd-11eb-9744-1d41e54d4521.png" width="270px" height="191px"/></p>|
## 11. Homography Transform
| origin Image| paper image | homography transform image|
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97965890-634fb980-1dfe-11eb-92d1-f57bc03548aa.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97965896-664aaa00-1dfe-11eb-869c-6d14701e4e37.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97965928-72366c00-1dfe-11eb-8966-9ac26300ed73.png" width="270px" height="191px"/></p>|
## 12. Stereo matching
| Left Image| Right image | 7x7 Disparity map | 9x9 Disparity map|
| ------------ | ------------- | ------------- | ------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97966237-ea049680-1dfe-11eb-8a9e-8a9dff3a79f5.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97966244-ecff8700-1dfe-11eb-941f-08269de68cc3.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97966214-e07b2e80-1dfe-11eb-9dd7-a1ff93fe3aa5.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97966221-e40eb580-1dfe-11eb-8731-e11736903c44.png" width="270px" height="191px"/></p>|
## 13. Expectation Maximization
| Clock Image| Clock Paint image | expectation Maximization image|
| ------------ | ------------- |------------- |
|   <img src="https://user-images.githubusercontent.com/67779811/97966524-4a93d380-1dff-11eb-8146-290c560ec325.png" width="270px" height="191px"/></p> |<img src="https://user-images.githubusercontent.com/67779811/97966534-4d8ec400-1dff-11eb-8068-17168dcf0472.png" width="270px" height="191px"/></p>|<img src="https://user-images.githubusercontent.com/67779811/97966512-45cf1f80-1dff-11eb-8fb6-8c5af0953a15.png" width="270px" height="191px"/></p>|
