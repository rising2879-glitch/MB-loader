# Kao MB Shader Bridge (โครงงานเริ่มต้น)

โครงงานนี้เป็น **Native Mod สำหรับ Levi Launcher** ที่มีจุดประสงค์เริ่มจากตรวจสอบว่า Levi โหลด `.so` ได้และเรียก lifecycle ของมอดได้จริง ก่อนเชื่อมโค้ด Shader จาก MB Loader

## สถานะจริง
- มีซอร์ส C++ สำหรับ Native Mod ตาม API สาธารณะของ Levi
- มี `manifest.json` และ GitHub Actions workflow สำหรับสร้างไฟล์ `.levipack` บน ARM64
- **รุ่นนี้ยังไม่เปิดใช้งาน Shader และยังไม่ได้เรียกไลบรารีของ MB Loader**
- ยังไม่ได้ build หรือทดสอบบน Levi Launcher 1.5.25
- การสร้างแพ็กเกจสำเร็จไม่ได้ยืนยันว่า Shader จะทำงาน การเชื่อม MB Loader ต้องตรวจสอบเวอร์ชัน Minecraft และลำดับการเริ่มต้นก่อน

## วิธีสร้างไฟล์บนมือถือผ่าน GitHub Actions
1. สร้าง repository ใหม่บน GitHub แล้วอัปโหลดไฟล์ทั้งหมดในโฟลเดอร์นี้
2. เปิดแท็บ **Actions** ของ repository และอนุญาตให้ workflow ทำงาน หาก GitHub ขออนุญาต
3. รัน workflow **Build Levi Native Mod** หรือ push commit ใหม่
4. เมื่อ workflow สำเร็จ ให้เปิด run ล่าสุด แล้วดาวน์โหลด artifact `KaoMBShaderBridge-levipack`
5. แตก ZIP artifact ที่ดาวน์โหลด จะมี `KaoMBShaderBridge.levipack` อยู่ข้างใน
6. นำ `.levipack` ไปนำเข้าใน Levi Launcher

> หาก build ไม่ผ่าน ให้ส่ง log ของขั้นตอนที่เป็นสีแดงมาได้ อย่าเดาว่าไฟล์ใช้ได้หากยังไม่ผ่านการ build

## ทำไมเริ่มจากมอดตรวจสอบก่อน
ไฟล์ native ของ MB Loader มีจุดเชื่อมต่อกับแอป MB Loader และไม่ได้เป็น Levi Native Mod โดยตรง การโหลด `.so` แบบสุ่มหรือเรียก hook ก่อนเกมพร้อมอาจทำให้ Minecraft เด้งได้ ขั้นต่อไปต้องพอร์ต/เชื่อม source ของตัว redirector และ MaterialBinLoader ให้เข้ากับ ABI และเวอร์ชันเกมจริง
