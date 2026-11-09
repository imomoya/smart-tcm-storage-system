"""上位机主程序：Python，经 CH340 串口收下位机数据。

初始框架：串口接收、库存表、导出 CSV 的流程已定，
硬件未到货，尚未与实物联调。

用法：
    pip install -r requirements.txt
    python main.py --port COM3 --baud 115200   # Windows，端口按设备管理器里的改
    python main.py --port /dev/ttyUSB0 --baud 115200  # Linux
按 Ctrl+C 退出，退出时自动导出 records.csv。
"""

import argparse
import sys

import serial

from inventory import Inventory
from protocol import parse_data_line


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", required=True, help="串口号，如 COM3 或 /dev/ttyUSB0")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--out", default="records.csv", help="退出时导出的 CSV 文件")
    args = parser.parse_args()

    inventory = Inventory()
    print(f"正在连接 {args.port}，波特率 {args.baud}，按 Ctrl+C 退出并导出 {args.out}")

    try:
        ser = serial.Serial(args.port, args.baud, timeout=1)
    except serial.SerialException as e:
        print(f"打不开串口 {args.port}：{e}", file=sys.stderr)
        print("先确认 CH340 已插好、端口号没写错、串口没被其他程序占用。", file=sys.stderr)
        return 1

    try:
        while True:
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            if not line:
                continue
            data = parse_data_line(line)
            if data is None:
                print(f"收到了看不懂的一行：{line}")
                continue
            inventory.update(data)
            inventory.show()
            print("-" * 40)
    except KeyboardInterrupt:
        print("\n正在导出 CSV……")
        inventory.export_csv(args.out)
        print(f"已导出到 {args.out}")
    finally:
        ser.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
