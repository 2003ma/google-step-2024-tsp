#!/bin/bash

# 引数が1つ指定されているか確認
if [ $# -ne 2 ]; then
  echo "Usage: $0 <execute_file><output_folder>"
  exit 1
fi

# 実行ファイルを指定
execute_file=$1
output_folder=$2

# 実行ファイルの存在を確認
if [ ! -f "$execute_file" ]; then
  echo "Error: Execute file $execute_file does not exist."
  exit 1
fi

# 入力ファイルの範囲を指定
for i in `seq 0 6`; do
  # 入力ファイルの存在を確認
  input_file="input/input_${i}.csv"
  if [ -f "$input_file" ]; then
    # 実行ファイルを実行し、出力をファイルに保存
    "$execute_file" "$input_file" > "output/$output_folder/output_${i}.csv"
    echo "Processed $input_file, output saved to output_${i}.csv"
  else
    echo "$input_file does not exist"
  fi
done
