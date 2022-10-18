#修改为自己的app.py所在的路径
path=/home/user/cwm/pythonmicroserver-update_weights/app.py
# GPU号，-1表示CPU, 默认0
GPU_MODE=0
# 批次大小,默认1
batch=1
# 端口号, 默认5000
port=5000
# 参数赋值 eg: startServer.sh 0 5001 2
if [[ $# == 1 ]]
then
   GPU_MODE=$1
elif [[ $# == 2 ]]
then
   port=$2
elif [[ $# == 3 ]]
then
   batch=$3
fi
# 启动服务，指定GPUID，端口号，batch大小
nohup python $path --GPU_MODE $GPU_MODE --port $port --batchSize $batch >> nohup.out &

