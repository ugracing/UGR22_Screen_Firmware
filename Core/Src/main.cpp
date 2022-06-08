/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//extern "C" {
//#include "MY_ILI9341.h"
//}
#include "S25FL.h"
#include "UGRScreen.h"
#include "UGRScreenField.h"
#include "Vladimir24pt.h"
#include "FreeSans20pt7b.h"
#include "FreeSans10pt7b.h"
#include "FreeSans35pt7b.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

uint8_t buf[ILI9341_WIDTH*2];

uint8_t col_ready = 0;
uint8_t SPI_DMA_BUSY = 0;

static struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
  unsigned char	 pixel_data[40 * 30 * 2 + 1];
} meme = {
  40, 30, 2,
  "\206I\246Y\346a\346a$\061\003)\004\061$\071\205I\205I\346YGjgr\310\212\250\202\310"
  "\212g\202'j\305Y\006z\314\323\312\343\353\343\014\344J\313Gz#\071\003)#)#)\003)\343"
  "\040\342\030\303\030\343\030\343\040\245Y\252\303+\334\013\334\205I\206Q\306Q\003"
  "\061\343($\071\205I\347a'rGrGrGzgz\247\202\207\202\207\202FzFzGz\345i\310\242"
  "J\313\252\343\313\333g\202\204I\244I'b\245Q\245I\204A\245I\346Y\245Q\342"
  "\060\303\040\343(&r\014\314\013\334eAEA\004\061\003)E\071\306Y\346a\346a\306a\305Y"
  "\305Y\305Y\305Y\345a\006j\006j\006b\006jGzgz\006r\250\232)\273\350\242\006j\247\202f"
  "z\345a\204IDAC\071$A\205Q&r\310\222Gr$A\003\071\250\222\313\323eI\004\071$\071eA"
  "\246Q\246Y\245Y\245Y\205Q\205I\204QdIDIdI\245Q\205Q\204I\245Y\006jgzGr&r\310"
  "\232\351\232\250\212\250\212gz\006b\245QCA$A\004\071$\071#A\204ag\212\250\222\006"
  "jcQJ\263EAD\071\205I\205Q\205Q\205Q\205I\204I\245Q\245Q\245QdIdIDIDICACA\204"
  "I\245Q\006jhz&rg\202\310\212\310\212gzgrFj&j\305a\204QdICA#\071$AeQ\346qG\202"
  "\245a\351\222eAeIeIeIeIDAeI\246YGr*\223\253\253\354\253\253\233gr\204IC\071"
  "D\071DA\204I\305Y&jfz\207\202\250\212\247\202Fr\247\202\211\253l\314.\335"
  "o\335\215\304)\233\305adIdI\244Q\006rgz\011\213\205AeADAD\071$\061\003\061D\071\205"
  "AGb\210r\310z\011\203j\213\213\213Gb#\071\003\061#\071dA\244I\345Y&r\207\202\350"
  "\212\247\202\207\202\212\263,\324L\314\315\274/\275\256\264\313\253*\223"
  "\305YDA\205I\306a'j\251r\003!$!e\061\343\040\343\040\003!\343\040\003)$)D)$)\004!\003)"
  "\343\040\343\040\303\040\343(#\061d\071\245I\345Q\346ah\202\011\223\207\202\006j"
  "\245Q\003\071\004\061\303\040\343\040\003!\003!\003!\343\030\344\030\004!\303\030\303\040\343"
  "\040\004)\004!\004\031\004)\205\071\347Q\347Y\010b\007Z\306I\206\071HJ\205\061\305\071\204"
  "\061$)\003)\343\040\343\040\204\061\210JhJ\251ZGZ\003)\003!D\061d\061D)d\061\245\071\245"
  "I'b\250rGb\245A$!\003!\343\030\302\030eI\205A\343\040$)$\061D\071E\071\205A\003)\343"
  "\040\303\030\306\061\306\061\253{\314\203\352b\245A\205A\205\071\006R\207r\310\212"
  "\247z&RD)\246\071\205\061\343\030\343\030\343\030iJ\305\071\210R&J\345A\246AD\061"
  "\003!\306A\206\071\307Y\347Ye\071\346A\246IfA\206I\347Y\346Q\007Zhr\210r\350\202"
  "\314\253\313\253\014\264\313\243Gb\210b\350\202I\253\013\324L\324\254\233g"
  "b\313\243\011\213\250\202+\213+\203\311r\012{*{k{\213\203\012shZ\005Z\314\253"
  "\245A\347Q\306Q\306I\306I\306Y\346a\006b\346a\007jgz\250\212I\243,\324\315\344"
  "\015\335\015\325\016\325\310r\210rj\263\013\324.\355\016\345\254\233\250jo\355"
  "\015\345+\304\212\263\350\232\010\233\350\222\011\223\310\212\206z\350z\212"
  "\233\252\243\215\314\310rj\233hr\214\223'j\213\263j\303J\263\011\253J\273"
  "\313\313,\324\215\344\315\344\355\344\314\334\214\334m\314\245IFj\353\323"
  "\214\344\217\355\217\355gj\245\071\014\304l\344\316\354\016\355.\355.\345\015"
  "\335\254\314\354\324m\315\216\325n\325K\264o\325I{,\344\314\303K\243*\213"
  "\354\303l\354l\354l\354\215\354,\344\313\323\253\303\212\263j\263\010\253"
  "\250\222\006j\205\071\210z\252\323\312\333l\354\255\354\212\253\306A\347YG\202"
  "g\222\011\253\313\303l\334\315\344\254\344\355\334\014\325\014\315\015\315\312"
  "\243\352\233l\244\351\272\012\303k\313\312\242\346i\213\253,\324m\334L\334"
  "\212\303\011\253\210\212hrGr\345Y\204A\305Q\006j\210\222\351\262\253\323m\354"
  "\255\344\255\334\313\273\012\223\245I\245I\346a\006rg\212\247\242)\273\212\303"
  "\313\313\313\313)\233gr\253\243l\314(\222H\232H\232\210\232\251\232'r\346"
  "a\306Y\346Y\346a\306Y\346Y\306Q\305Q\245I$I\246a\305i\305ag\202*\273,\334"
  "\317\344m\344\013\354\015\344\351\232dADAdA\204I\245Q\305Y\006jGzgzI\233\313"
  "\303\353\313\352\313\306q\346y\007z\007z\347q\306i\205YdQDI$A$A$A#ADA#\071\343"
  "\070$ADIdI\346aG\212\210\232\351\252\011\263\011\273\254\313\352\242#A\004\071"
  "\003\071\003\071\003\071$AdI\346af\202(\253\211\303\251\313\252\323\205Y\205a\246"
  "i\306i\306a\306aDI#\071$\071$\071\004\061$\071\245I\246I\003\061$\061$A\004\071\004\071#A"
  "DQ\306i\007z\007r\245Y#I\351\202\306Q\343(\003\061#\071#\071\003\071\003\071#A\245Q\006r\247"
  "\232I\303j\323EQeY\245a\347q\007j\346a$\071\003)\004)\343\040\303\030\343\040\343\040"
  "\343\040\302\030\303\030\302\030\303\030\343\040\343(\003\061\003\061\343(\343(\003)\205"
  "AGjgjD\061\343\040\342\040$\071$\071$\071\003\071#A\205YFr\247\232\011\273DQeQ\245"
  "a\007r'r\205I\003)\303\030\303\030\303\030\303\030\343\030\303\030\303\030\302\030\303"
  "\030\303\030\303\020\303\030\303\030\303\030\303\030\343\030\343\040D\071\205I\245"
  "I\305Q\245I\205AD\071\302\040\343\040D\071$A$ADI\305aFzf\212DIdQ\306iGz\007b\003"
  "\061\302\030\303\030\343\030\003!D)$)\004)\004)\343\040\003!\343\040\303\040\242\040\242"
  "\030\303\030\343\040e\071\306Q\205I\244I\006Z\245AD\061d\071#)\343\030\303\030\003)D"
  "A$A#AdQ\005j&zDIdQ\306iH\202\246Q\003!\343\040\004)\004\061\004\061e\071\206\071\206\071"
  "\246\071\246\071\205\061\306AD\061\246\071e\071D\061\245A\245AGZ\351rM\234M\244"
  ".\224e\061\303\030\303\030\303\040\303\030\303\040\004\071$\071$ADI\305a\346iDIeQ\346"
  "ihz\245Q$\061$)d\071D\071\004\061\344\060\004\061D\061e\071e\061\205\071\306\071\306\071"
  "\306\071\306A\007J\210R\311b,s\012k)s\350jhR\343\040\342\040\343\040\344\040\303"
  "\030\303\040\004\061#\071#\071DI\205Y\205aEIeQ&r\010\243-\314\250\212\351\202*\223"
  "\012\213$\071\004\061\344\060\343\060\343($)\205\061\205\061\205\061\306A\211Z\351"
  "jj{\253\213\013\224\256\254\216\254P\315\314\263\352\272\311\232\342\070\343"
  "\040\302\040\343\040\343(\003\061#\071dI\205YdQeI\245Y\250\222\014\324\215\354L\324"
  "\207\212gzj\243\305Q$\061$\061\003\061\343\060\343\060$A\007j\007j\311r\213\203k\203"
  "\216\254\014\244\017\305\316\314L\314\213\323J\343j\333\312\313J\243&b&bFb"
  "CA$I\245Y\345a\245YdQEI\245QG\202\313\313\212\303\014\314j\243&j\250\212\254"
  "\253\250rDA\003\061#\061#\071DQ&\202\310\252*\303*\303)\303*\313j\323\253\333"
  "\213\343J\343\351\322\011\273\013\314l\334I\233\345Y%r\313\273j\253\310\212"
  "Fr\006j\245Y\245QD\071eA\205Y\210\212\351\232\250\222\011\233\006bgrI\243j\253"
  "j\243J\243J\233\210z\305YDI#I#Q\205i&zG\212h\212G\202\346q\006r)\233l\314\254"
  "\334L\324\207z\305Q\350\212\013\304\312\273)\233Fr\345Y\305QFbD\071D\071DA\205"
  "Q(r\007j\006b\245Q\346Qgr\310\212j\253J\263\213\263\212\273J\263J\253\011\243"
  ")\253\011\243)\243I\253j\253\313\273\353\303\013\324+\324l\334,\324\350\222"
  "\204I\204Ij\243\013\304\212\253\207zFb%ZFZ\352jD\071D\071D\071DA\205I\346Q\245"
  "A\245Ad\071eA\305Y\250\202\250\212\012\243*\253k\273I\253j\263I\273I\303\211"
  "\313\353\323\013\334\013\334\013\324,\344\352\323\353\313k\253\006b\205A\207r"
  "\353\273\212\243\350\202fjFj&Z\305Q\261\254D\071D\071D\071d\071dA\205Ad\071#)"
  "\003)\003)\245I\346Y'j\250\202\311\212\012\243\010\233)\253\011\253\351\242\011\253"
  "j\273I\263\212\303j\303\212\313\252\303\350\232\305YC\071$\061\010\213i\233"
  "\350\202\207jfb%Z\204I\205a\245y",
};

unsigned char black[40 * 30 * 2 + 1];

struct DTA_CAN_Data {
	int16_t RPM = 0;
	int16_t TPS = 0;
	int16_t wTemp = 0;
	int16_t aTemp = 0;
	int16_t mapKpa = 0;
	int16_t lambdax1000 = 0;
	int16_t KPHx10 = 0;
	int16_t oKpa = 0;
	int16_t fuelKpa = 0;
	int16_t oTemp = 0;
	int16_t voltsx10 = 0;
	int16_t fuelConL_100kmx10 = 0;
	int16_t gear = 0;
	int16_t advanceDegx10 = 0;
	int16_t injectionMsx100 = 0;
	int16_t fuelConL_Hrx10 = 0;
	int16_t ana1mV = 0;
	int16_t ana2mV = 0;
	int16_t ana3mV = 0;
	int16_t camAdvx10 = 0;
	int16_t camTargx10 = 0;
	int16_t camPWMx10 = 0;
	int16_t crankErr = 0;
	int16_t camErr = 0;
	int16_t cam2advx10 = 0;
	int16_t cam2Targx10 = 0;
	int16_t cam2PWMx10 = 0;
	int16_t extern5V = 0;
	int16_t injDutyCyc = 0;
	int16_t lambdaPIDTarg = 0;
	int16_t lambdaPIDAdj = 0;
	int16_t ecuSwitches = 0;
	int16_t rdSpeed = 0;
	int16_t rudSpeed = 0;
	int16_t ldSpeed = 0;
	int16_t ludSpeed = 0;
	int16_t rightLambda = 0;
};

struct DTA_CAN_Data ecuData;


CAN_RxHeaderTypeDef pRxHeader; //declare header for message reception
CAN_RxHeaderTypeDef rxCopy;
uint8_t rxData[8];

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;
DMA_HandleTypeDef hdma_spi1_tx;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
//	col_ready = 1;
	HAL_SPI_Transmit_DMA(&hspi3, buf, ILI9341_WIDTH);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	col_ready = 2;
	HAL_SPI_Transmit_DMA(&hspi3, buf+ILI9341_WIDTH, ILI9341_WIDTH);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	col_ready++;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &pRxHeader, rxData);
	//When in filter list mode, can hearders have no info for some reason, other than what item of the list they met, so looking for ID doesnt work
	if(pRxHeader.ExtId == 0x2000){
		ecuData.RPM = rxData[1] << 8 | rxData[0];
		ecuData.TPS = rxData[3] << 8 | rxData[2];
		ecuData.wTemp = rxData[5] << 8 | rxData[4];
		ecuData.aTemp = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2001){
		ecuData.mapKpa = rxData[1] << 8 | rxData[0];
		ecuData.lambdax1000 = rxData[3] << 8 | rxData[2];
		ecuData.KPHx10 = rxData[5] << 8 | rxData[4];
		ecuData.oKpa = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2002){
		ecuData.fuelKpa = rxData[1] << 8 | rxData[0];
		ecuData.oTemp = rxData[3] << 8 | rxData[2];
		ecuData.voltsx10 = rxData[5] << 8 | rxData[4];
		ecuData.fuelConL_100kmx10 = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2003){
		ecuData.gear = rxData[1] << 8 | rxData[0];
		ecuData.advanceDegx10 = rxData[3] << 8 | rxData[2];
		ecuData.injectionMsx100 = rxData[5] << 8 | rxData[4];
		ecuData.fuelConL_Hrx10 = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2004){
		ecuData.ana1mV = rxData[1] << 8 | rxData[0];
		ecuData.ana2mV = rxData[3] << 8 | rxData[2];
		ecuData.ana3mV = rxData[5] << 8 | rxData[4];
		ecuData.camAdvx10 = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2005){
		ecuData.camTargx10 = rxData[1] << 8 | rxData[0];
		ecuData.camPWMx10 = rxData[3] << 8 | rxData[2];
		ecuData.crankErr = rxData[5] << 8 | rxData[4];
		ecuData.camErr = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2006){
		ecuData.cam2advx10 = rxData[1] << 8 | rxData[0];
		ecuData.cam2Targx10 = rxData[3] << 8 | rxData[2];
		ecuData.cam2PWMx10 = rxData[5] << 8 | rxData[4];
		ecuData.extern5V = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2007){
		ecuData.injDutyCyc = rxData[1] << 8 | rxData[0];
		ecuData.lambdaPIDTarg = rxData[3] << 8 | rxData[2];
		ecuData.lambdaPIDAdj = rxData[5] << 8 | rxData[4];
		ecuData.ecuSwitches = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2008){
		ecuData.rdSpeed = rxData[1] << 8 | rxData[0];
		ecuData.rudSpeed = rxData[3] << 8 | rxData[2];
		ecuData.ldSpeed = rxData[5] << 8 | rxData[4];
		ecuData.ludSpeed = rxData[7] << 8 | rxData[6];
	}
	if(pRxHeader.ExtId == 0x2001){
		ecuData.rightLambda = rxData[1] << 8 | rxData[0];
	}
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI3_Init(void);
static void MX_SPI1_Init(void);
static void MX_CAN1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
S25FL flash;

CAN_FilterTypeDef sFilterConfig; //declare CAN filter structure

void drawGrid(){
	for(int w = 20; w < 240; w+= 20){
		ILI9341_drawLine(0, w, 319, w, COLOR_ORANGE);
	}
	for(int h = 20; h < 320; h+= 20){
		ILI9341_drawLine(h, 0, h, 239, COLOR_ORANGE);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_SPI3_Init();
  MX_SPI1_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  //Init LCD
  UGR_Screen screen = UGR_Screen(&hspi1, LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_DC_GPIO_Port, LCD_DC_Pin, LCD_RST_GPIO_Port, LCD_RST_Pin);

  //Init Flash
  flash = S25FL(&hspi3, FLASH_CS_GPIO_Port, FLASH_CS_Pin);
  flash.begin();


  //DEBUG print flash max address
  uint32_t maxadd = flash.getMaxAddress();
  char str[128];
  sprintf(str, "maxadd: %d\n\r", maxadd);
  HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);


  //CAN test code
  //So in 32 bit mode you have to split the 32 bit filter ID into 2 16 bit segments, to be put into IdHigh and IdLow... which are both 32 bit??? REEEE
  	uint32_t canFiltMask 	= 0x1FFFFFF0;
  	uint32_t canFiltMask_STD = canFiltMask & 0x7FF; //Separate mask into its standard and extended parts
  	uint32_t canFiltMask_IDE = canFiltMask >> 11;
  	uint32_t canFiltID 		= 0x2000;
  	uint32_t canFiltID_STD = canFiltID & 0x7FF; //Separate ID into its standard and extended parts
	uint32_t canFiltID_IDE = canFiltID >> 11;

	sFilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0; //set fifo assignment
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterIdHigh = (canFiltID_STD << 5) & (canFiltID_IDE >> 13);
    sFilterConfig.FilterIdLow =  (canFiltID_IDE << 3) & 0x4;
	sFilterConfig.FilterMaskIdHigh = (canFiltMask_STD << 5) & (canFiltMask_IDE >> 13);
	sFilterConfig.FilterMaskIdLow =  (canFiltMask_IDE << 3) & 0x4;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //set filter scale
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterActivation=ENABLE;

	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig); //configure CAN filter

	HAL_CAN_Start(&hcan1); //start CAN
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //Convert stored image to usable format
  //fucking gimp is useless, this is the easiest way I can get gimp generated images to fucking work!
  uint8_t c;
  for(uint32_t i = 0; i < meme.height * meme.width * meme.bytes_per_pixel; i+=2){
	  c = meme.pixel_data[i];
	  meme.pixel_data[i] = meme.pixel_data[i+1];
	  meme.pixel_data[i+1] = c;
  }


  ILI9341_Fill(COLOR_BLACK);
  uint32_t xpos = 0;
  uint32_t ypos = 0;
//  ILI9341_SetCursorPosition(xpos, ypos, xpos + meme.width - 1,  ypos + meme.height - 1);
//  HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//  HAL_SPI_Transmit_DMA(&hspi1, meme.pixel_data, meme.height * meme.width * meme.bytes_per_pixel);
//
//  while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
//
//  ILI9341_SetCursorPosition(ILI9341_HEIGHT - meme.width, ILI9341_WIDTH - meme.height, ILI9341_HEIGHT - 1,  ILI9341_WIDTH - 1);
//  HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//  HAL_SPI_Transmit_DMA(&hspi1, meme.pixel_data, meme.height * meme.width * meme.bytes_per_pixel);
//
//  HAL_Delay(1);
//  while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

  UGR_ScreenField rpmTitleField = 			UGR_ScreenField(2, 0, "RPM", 				FreeSans10pt7b, &screen);
  UGR_ScreenField rpmField = 				UGR_ScreenField(10, 20, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField mphTitleField = 			UGR_ScreenField(2, 60, "MPH", 				FreeSans10pt7b, &screen);
  UGR_ScreenField mphField = 				UGR_ScreenField(10, 80, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField oilTempTitleField = 		UGR_ScreenField(2, 120, "Oil C", 			FreeSans10pt7b, &screen);
  UGR_ScreenField oilTempField = 			UGR_ScreenField(10, 140, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField oilKpaTitleField = 		UGR_ScreenField(2, 180, "Oil Kpa", 			FreeSans10pt7b, &screen);
  UGR_ScreenField oilKpaField = 			UGR_ScreenField(10, 200, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField waterTempTitleField = 	UGR_ScreenField(260, 0, "Cool C", 			FreeSans10pt7b, &screen);
  UGR_ScreenField waterTempField = 			UGR_ScreenField(240, 20, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField voltsTitleField = 		UGR_ScreenField(260, 60, "Volts", 			FreeSans10pt7b, &screen);
  UGR_ScreenField voltsField = 				UGR_ScreenField(240, 80, "", 				FreeSans20pt7b, &screen);
  UGR_ScreenField throttleTitleField = 		UGR_ScreenField(260, 120, "TPS", 			FreeSans10pt7b, &screen);
  UGR_ScreenField throttleField = 			UGR_ScreenField(240, 140, "", 				FreeSans20pt7b, &screen);


//  UGR_ScreenField brakeFrontKpaTitleField = UGR_ScreenField(200, 25, "BRAKE F Kpa", 		FreeSans10pt7b, &screen);
//  UGR_ScreenField brakeFrontKpaField = 		UGR_ScreenField(200, 40, "", 				FreeSans20pt7b, &screen);
//  UGR_ScreenField brakeRearKpaTitleField = 	UGR_ScreenField(200, 55, "BRAKE R Kpa", 	FreeSans10pt7b, &screen);
//  UGR_ScreenField brakeRearKpaField = 		UGR_ScreenField(200, 70, "", 				FreeSans20pt7b, &screen);

  UGR_ScreenField gearTitleField = 			UGR_ScreenField(130, 20, "Gear", 			FreeSans10pt7b, &screen);
  UGR_ScreenField gearField = 				UGR_ScreenField(130, 45, "", 				FreeSans35pt7b, &screen);

  int can_mph = 0;
  int can_gear = 0;
  char tmp_str[9];

//  drawGrid();

  //for fit testing of fields while CAN is disconnected
  ecuData.RPM = 12000;
  ecuData.KPHx10 = 1200;
  ecuData.oTemp = 112;
  ecuData.oKpa = 650;
  ecuData.voltsx10 = 135;
  ecuData.wTemp = 101;
  ecuData.TPS = 100;
  ecuData.gear = 5;

  while (1)
  {
	  sprintf(tmp_str, "%d", ecuData.RPM);
	  rpmField.update(tmp_str);
	  sprintf(tmp_str, "%d", (int)((float)ecuData.KPHx10 * 0.0621371));
	  mphField.update(tmp_str);
	  sprintf(tmp_str, "%d", ecuData.gear);
	  gearField.update(tmp_str);
	  sprintf(tmp_str, "%d", ecuData.oTemp);
	  oilTempField.update(tmp_str);
	  sprintf(tmp_str, "%d", ecuData.oKpa);
	  oilKpaField.update(tmp_str);
	  sprintf(tmp_str, "%d.%d", ecuData.voltsx10 / 10, ecuData.voltsx10 % 10);
	  voltsField.update(tmp_str);
	  sprintf(tmp_str, "%d", ecuData.wTemp);
	  waterTempField.update(tmp_str);
	  sprintf(tmp_str, "%d", ecuData.TPS);
	  throttleField.update(tmp_str);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
  /** Enable the SYSCFG APB clock
  */
  __HAL_RCC_CRS_CLK_ENABLE();
  /** Configures CRS
  */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_LSE;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000,32768);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 8;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_DC_Pin|FLASH_CS_Pin|LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_DC_Pin FLASH_CS_Pin LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_DC_Pin|FLASH_CS_Pin|LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
