"""串口协议：与 firmware/src/protocol.c 对应，纯文本行。

上行：DATA,<格号>,<重量克>,<温度>,<湿度>
  例：DATA,1,123.4,25.1,60.2
下行：SET,TH,<温度上限>,<湿度上限> / TARE,<格号>
  例：SET,TH,30,75 / TARE,1
"""


def parse_data_line(line: str):
    """解析一行上行数据，成功返回 dict，格式不对返回 None。"""
    parts = line.strip().split(",")
    if len(parts) != 5 or parts[0] != "DATA":
        return None
    try:
        return {
            "slot": int(parts[1]),
            "weight_g": float(parts[2]),
            "temp_c": float(parts[3]),
            "humidity": float(parts[4]),
        }
    except ValueError:
        return None


def build_set_threshold(temp_limit: float, hum_limit: float) -> str:
    return f"SET,TH,{temp_limit},{hum_limit}\n"


def build_tare(slot: int) -> str:
    return f"TARE,{slot}\n"
