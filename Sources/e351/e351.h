#ifndef _E351_H_
#define _E351_H_


#define D0(x)     (PTB->PDOR = (x)?0x00000004:0)
#define D1(x)     (PTB->PDOR = (x)?0x00000008:0)
#define D2(x)     (PTC->PDOR = (x)?0x00004000:0)
#define D3(x)     (PTC->PDOR = (x)?0x00008000:0)
#define D4(x)     (PTC->PDOR = (x)?0x00010000:0)
#define D5(x)     (PTC->PDOR = (x)?0x00020000:0)
#define D6(x)     (PTC->PDOR = (x)?0x00000001:0)
#define D7(x)     (PTC->PDOR = (x)?0x00000002:0)
#define D8(x)     (PTC->PDOR = (x)?0x00000004:0)
#define D9(x)     (PTC->PDOR = (x)?0x00000008:0)
#define D10(x)    (PTB->PDOR = (x)?0x00000010:0)
#define D11(x)    (PTB->PDOR = (x)?0x00000020:0)
#define D12(x)    (PTE->PDOR = (x)?0x00000100:0)
#define D13(x)    (PTE->PDOR = (x)?0x00000200:0)
#define D14(x)    (PTD->PDOR = (x)?0x00008000:0)
#define D15(x)    (PTD->PDOR = (x)?0x00010000:0)
#define D16(x)    (PTE->PDOR = (x)?0x00000008:0)

#define CS(x)     (PTE->PDOR = (x)?0x00000080:0)
#define CS_H      (PTE->PSOR = 0x00000080)
#define CS_L      (PTE->PCOR = 0x00000080)

#define LOAD(x)   (PTA->PDOR = (x)?0x00000040:0)
#define LOAD_H    (PTA->PSOR = 0x00000040)
#define LOAD_L    (PTA->PCOR = 0x00000040)

#define WR(x)     (PTA->PDOR = (x)?0x00000080:0)
#define WR_H      (PTA->PSOR = 0x00000080)
#define WR_L      (PTA->PCOR = 0x00000080)


#define load_clk()      CS_H,LOAD_H,LOAD_L //Load输出高 CS输出高

#define one_clk()       WR_H,WR_L           //WR输出高 

#define cs_on()         CS_L,WR_L           //CS输出低 WR输出低

#define cs_off()        CS_H                //PB.0--CS输出高


#define Config_Head 0xc00
#define Config_Data 0x012
#define Config2_Data0 0x33e
#define Config3_Data0 0x7cf
#define Config2_Data6 0x3ff
#define Config3_Data6 0xfff
#define Config2_Data1 0x307
#define Config3_Data1 0x6cf
#define Config2_Data2 0x317
#define Config3_Data2 0xbcf
#define Config2_Data3 0x321
#define Config3_Data3 0x1cf
#define Config2_Data4 0x327
#define Config3_Data4 0x8cf
#define Config2_Data5 0x33f
#define Config3_Data5 0xfcf
#define Control_Head 0x800
#define Control_RGBData 0x3ff
#define Control_RGB0Data 0x000
#define Control_BData 0x3ff




void prvE351RefreshTask(void *pvParameters );

#endif
/* end of file*/