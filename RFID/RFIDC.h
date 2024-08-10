class RFID{
#define CommandReg 2
#define ComIEnReg 4
#define DivIEnReg 6
#define ComIrqReq 8
#define DivIrqReg 10
#define ErrorReg 12
#define Status1Reg 14
#define Status2Reg 16
#define FIFODataReg 18
#define FIFOLevelReg 20
#define WaterLevelReg 22
#define ControlReg 24
#define BitFramingReg 26
#define CollReg 28 
#define CmdIdle 0
#define CmdMem 1
#define CmdGenRandID 2
#define CmdCalcCRC 3
#define Cmdransmit 4
#define CmdNoCmdChange 7
#define CmdReeive 8
#define CmdTranscieve 12
#define CmdMFAuthent 14
#define CmdSoftReset 15

public:
	RFID(int SCK, int MOSI, int MISO, int IRQ, int NSS); 
  byte SendData(boolean RW, byte Address, byte* Input);
  byte CmdReg(boolean RW, boolean RcvOff, boolean PowerDown, byte Command);
private:
  int NSS,SCK,MOSI,MISO,RST;
};
