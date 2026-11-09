"""库存表：4 格的最新重量 / 温湿度 / 报警状态，支持导出 CSV。"""

import csv
from datetime import datetime

SLOT_COUNT = 4
WEIGHT_LOW_LIMIT_G = 50.0  # 缺药报警阈值（克），初值，待实测后调


class Inventory:
    def __init__(self):
        # 每格：{"weight_g": float, "temp_c": float, "humidity": float, "updated": str}
        self.slots = {i: {} for i in range(1, SLOT_COUNT + 1)}
        self.records = []  # 取补记录：每条是 dict，含时间、格号、重量

    def update(self, data: dict):
        slot = data["slot"]
        if slot not in self.slots:
            return
        self.slots[slot] = {**data, "updated": datetime.now().isoformat(timespec="seconds")}
        self.records.append({**data, "time": datetime.now().isoformat(timespec="seconds")})

    def is_low(self, slot: int) -> bool:
        weight = self.slots.get(slot, {}).get("weight_g")
        return weight is not None and weight < WEIGHT_LOW_LIMIT_G

    def show(self):
        print("格号  重量(g)  温度  湿度  状态")
        for slot in range(1, SLOT_COUNT + 1):
            info = self.slots.get(slot, {})
            if not info:
                print(f"{slot}    -        -     -     未收到数据")
                continue
            status = "缺药" if self.is_low(slot) else "正常"
            print(f"{slot}    {info['weight_g']:<8} {info['temp_c']:<5} {info['humidity']:<5} {status}")

    def export_csv(self, path: str):
        """导出取补记录到 CSV。"""
        with open(path, "w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(f, fieldnames=["time", "slot", "weight_g", "temp_c", "humidity"])
            writer.writeheader()
            writer.writerows(self.records)
