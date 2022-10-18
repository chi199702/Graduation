1. 比如使用pycharm打开这个工程文件

2. pip install -r requirements.txt 以及必要的pytorch包，cuda

3. app.py 对应着以前的gitlab中的服务端，你可以使用gitlab中的java客户端(对应的分支名称为update_weights)去访问这个app.py文件

4. 简单起见，可以在test.py文件中定义好你图片的文件夹位置以及处理图片被保存的位置：

    ```python
       rootDir = "D:\CarData\img\img\imagesDemo"
       saved_path = r"D:\CarData\img\img\test"
    ```

5. 运行test.py文件即可，最后的保存文件的路径在你定义的saved_path中

6. 函数 HyperLPR_plate_recognition的返回结果分别代表eg：
    置信度[0.8,0.9]、坐标[[x,y,x,y],[x,y,x,y]]、车牌信息:["",""]
    





