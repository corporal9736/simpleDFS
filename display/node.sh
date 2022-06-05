#!/bin/bash
#在chunk_node下创建root0到root9的文件夹
#创建文件夹
for i in {0..9}
do
    mkdir -p /home/thunder/CODE/c/simpleDFS/display/chunk_node/root$i
done
#运行simpleDFS_chunk，启动9个chunk_node，其中，每个node的端口号为：9000+i，i为0到9
#log文件存放在/home/thunder/CODE/c/simpleDFS/display/chunk_node/log/
for i in {0..9}
do
    nohup ./simpleDFS_chunk 900$i $i > /home/thunder/CODE/c/simpleDFS/display/chunk_node/log/chunk_node$i.log 2>&1 &
done