#!/bin/bash
###
 # @Author: flywes bg_weapon@163.com
 # @Date: 2024-04-15 18:54:34
 # @LastEditors: flywes bg_weapon@163.com
 # @LastEditTime: 2024-04-15 19:02:46
 # @FilePath: \ddns2_demo\server\test\copy_name.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 

# 源文件目录
SOURCE_DIR="./test"

# 目标文件目录
TARGET_DIR="./test"

# 文件名基础部分
FILENAME_BASE="big_bmp_"
FILENAME_SRC_BASE="big_bmp_1"

# 开始编码
START_NUMBER=1

# 结束编码
END_NUMBER=120

# 递增步长
INCREMENT=1

# 循环拷贝文件
for (( i = START_NUMBER; i <= END_NUMBER; i+=INCREMENT )); do
    formatted_number=$(printf "%03d" $i)
    # 构建源文件名和目标文件名
    src_file="${SOURCE_DIR}/${FILENAME_SRC_BASE}.bmp"
    tgt_file="${TARGET_DIR}/${FILENAME_BASE}${formatted_number}.bmp"

    # 拷贝文件
    cp "$src_file" "$tgt_file"
done

echo "批量拷贝完成。"