#!/bin/bash

# 入力ファイルの範囲を指定
for i in `seq 0 6`; do
  # 入力ファイルの存在を確認
  input_file="input_${i}.csv"
  if [ -f "$input_file" ]; then
    # solver_2_optプログラムを実行し、出力をファイルに保存
    ./klascal "$input_file" > "output_${i}.csv"
    echo "Processed $input_file, output saved to output_${i}.csv"
  else
    echo "$input_file does not exist"
  fi
done
