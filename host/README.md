# 上位机 host

Python，VS Code，经 CH340 串口与下位机通信。

## 状态

初始框架已写，尚未与实物联调。Python 语法已在本地检查通过，串口部分要等硬件到货才能实测。

## 文件

```
main.py         主程序：读串口、更新库存表、Ctrl+C 时导出 CSV
protocol.py     串口协议解析 / 组包，与 firmware/src/protocol.c 对应
inventory.py    库存表：4 格最新数据、缺药判断、导出 CSV
requirements.txt  pyserial
```

## 用法

```
pip install -r requirements.txt
python main.py --port COM3 --baud 115200   # Windows，端口按设备管理器里的改
python main.py --port /dev/ttyUSB0 --baud 115200  # Linux
```

按 Ctrl+C 退出，退出时自动导出 records.csv。

## 设计要求

- 串口接收下位机上传的数据
- 库存总览
- 取补记录查询
- 阈值设置下发
- 数据导出 CSV
