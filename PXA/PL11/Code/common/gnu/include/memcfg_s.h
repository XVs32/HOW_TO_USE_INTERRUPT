/* --------------------------------------------------------------------
;
;   Title     :  memcfg_s.h
;             :
;   Library   :
;             :
;   Developers:  MICROTIME MDS group
;             :
;   Purpose   :  Memory bank configuration file
;             :
;   Limitation:
;             :
;   Note      :
;             :
; --------------------------------------------------------------------
;   modification history :
; --------------------------------------------------------------------
;   Version| mod. date: |
;   V1.0   | 12/01/2006 | First release
; --------------------------------------------------------------------
;
; Note:
;
;       MICROTIME COMPUTER INC.
;
; -------------------------------------------------------------------*/
.equ  LAB_MODIFY,         1

#define MT_CONST(x, y)     .equ   x,   (y)

.ifdef 	LAB_MODIFY
	MT_CONST(CPU_520MHZ, 1)
.endif
	
	MT_CONST(NORMAL_TEST, 1)

    MT_CONST(CFG_DRAM_BASE,	0xA0000000)


	/*===========================================================
     * CPU Registers
     *==========================================================*/     

    MT_CONST(OSCR, 0x40A00010)
    
	/*===========================================================
     * ;;;;;;;;;;	GPIO Ddefination	;;;;;;;;;
     *==========================================================*/

    MT_CONST(GPI,  0)
    MT_CONST(GPO,  1)
    MT_CONST(GPIO, 0)
    MT_CONST(ALT1, 1)
    MT_CONST(ALT2, 2)
    MT_CONST(ALT3, 3)

    MT_CONST(GPIO_BASE,		0x40E00000)
    MT_CONST(GPLR0_OFFSET,	0x00)
    MT_CONST(GPLR1_OFFSET,	0x04)
    MT_CONST(GPLR2_OFFSET,	0x08)
    MT_CONST(GPDR0_OFFSET,	0x0C)
    MT_CONST(GPDR1_OFFSET,	0x10)
    MT_CONST(GPDR2_OFFSET,	0x14)

    MT_CONST(GPSR0_OFFSET,	     0x18)
    MT_CONST(GPSR1_OFFSET,	     0x1C)
    MT_CONST(GPSR2_OFFSET,	     0x20)
		
    MT_CONST(GPCR0_OFFSET,	     0x24)
    MT_CONST(GPCR1_OFFSET,	     0x28)
    MT_CONST(GPCR2_OFFSET,	     0x2C)

    MT_CONST(GRER0_OFFSET,	     0x30)
    MT_CONST(GRER1_OFFSET,	     0x34)
    MT_CONST(GRER2_OFFSET,	     0x38)

    MT_CONST(GFER0_OFFSET,	     0x3C)
    MT_CONST(GFER1_OFFSET,	     0x40)
    MT_CONST(GFER2_OFFSET,	     0x44)

    MT_CONST(GEDR0_OFFSET,	     0x48)
    MT_CONST(GEDR1_OFFSET,	     0x4C)
    MT_CONST(GEDR2_OFFSET,	     0x50)

    MT_CONST(GAFR0_L_OFFSET,	     0x54)
    MT_CONST(GAFR0_U_OFFSET,	     0x58)
    MT_CONST(GAFR1_L_OFFSET,	     0x5C)
    MT_CONST(GAFR1_U_OFFSET,	     0x60)
    MT_CONST(GAFR2_L_OFFSET,	     0x64)
    MT_CONST(GAFR2_U_OFFSET,	     0x68)
    MT_CONST(GAFR3_L_OFFSET,	     0x6C)
    MT_CONST(GAFR3_U_OFFSET,	     0x70)

    MT_CONST(GPLR3_OFFSET,	     0x100)
    MT_CONST(GPDR3_OFFSET,	     0x10C)
    MT_CONST(GPSR3_OFFSET,	     0x118)
    MT_CONST(GPCR3_OFFSET,	     0x124)
    MT_CONST(GRER3_OFFSET,	     0x130)
    MT_CONST(GFER3_OFFSET,	     0x13C)
    MT_CONST(GEDR3_OFFSET,	     0x148)

  
.ifdef GPIO_TEST

    MT_CONST(AF000,					(GPIO	<< 	0))
    MT_CONST(AF001,					(GPIO	<< 	2))
    MT_CONST(AF002,					(GPIO	<< 	4))
    MT_CONST(AF003,					(GPIO	<< 	6))
    MT_CONST(AF004,					(GPIO	<< 	8))
    MT_CONST(AF005,					(GPIO	<< 	10))
    MT_CONST(AF006,					(GPIO	<< 	12))
    MT_CONST(AF007,					(GPIO	<< 	14))
    MT_CONST(AF008,					(GPIO	<< 	16))
    MT_CONST(AF009,					(GPIO	<< 	18))
    MT_CONST(AF010,					(GPIO	<< 	20))
    MT_CONST(AF011,					(GPIO	<< 	22))
    MT_CONST(AF012,					(GPIO	<< 	24))
    MT_CONST(AF013,					(GPIO	<< 	26))
    MT_CONST(AF014,					(GPIO	<< 	28))
    MT_CONST(AF015,					(ALT2	<< 	30))
    MT_CONST(AF016,					(GPIO	<< 	0))
    MT_CONST(AF017,					(GPIO	<< 	2))
    MT_CONST(AF018,					(ALT1	<< 	4))
    MT_CONST(AF019,					(GPIO	<< 	6))
    MT_CONST(AF020,					(ALT1	<< 	8))
    MT_CONST(AF021,					(ALT2	<< 	10))
    MT_CONST(AF022,					(GPIO	<< 	12))
    MT_CONST(AF023,					(GPIO	<< 	14))
    MT_CONST(AF024,					(GPIO	<< 	16))
    MT_CONST(AF025,					(GPIO	<< 	18))
    MT_CONST(AF026,					(GPIO	<< 	20))
    MT_CONST(AF027,					(GPIO	<< 	22))
    MT_CONST(AF028,					(GPIO	<< 	24))
    MT_CONST(AF029,					(GPIO	<< 	26))
    MT_CONST(AF030,					(GPIO	<< 	28))
    MT_CONST(AF031,					(GPIO	<< 	30))
    MT_CONST(AF032,					(GPIO	<< 	0))
    MT_CONST(AF033,					(ALT2	<< 	2))
    MT_CONST(AF034,					(GPIO	<< 	4))
    MT_CONST(AF035,					(ALT1	<< 	6))
    MT_CONST(AF036,					(ALT1	<< 	8))
    MT_CONST(AF037,					(ALT1	<< 	10))
    MT_CONST(AF038,					(ALT1	<< 	12))
    MT_CONST(AF039,					(ALT2	<< 	14))
    MT_CONST(AF040,					(ALT2	<< 	16))
    MT_CONST(AF041,					(ALT1	<< 	18))
    MT_CONST(AF042,					(ALT1	<< 	20))
    MT_CONST(AF043,					(ALT2	<< 	22))
    MT_CONST(AF044,					(ALT1	<< 	24))
    MT_CONST(AF045,					(ALT2	<< 	26))
    MT_CONST(AF046,					(GPIO	<< 	28))
    MT_CONST(AF047,					(GPIO	<< 	30))
    MT_CONST(AF048,					(GPIO	<< 	0))
    MT_CONST(AF049,					(ALT2	<< 	2))
    MT_CONST(AF050,					(GPIO	<< 	4))
    MT_CONST(AF051,					(GPIO	<< 	6))
    MT_CONST(AF052,					(GPIO	<< 	8))
    MT_CONST(AF053,					(GPIO	<< 	10))
    MT_CONST(AF054,					(GPIO	<< 	12))
    MT_CONST(AF055,					(GPIO	<< 	14))
    MT_CONST(AF056,					(GPIO	<< 	16))
    MT_CONST(AF057,					(GPIO	<< 	18))
    MT_CONST(AF058,					(GPIO	<< 	20))
    MT_CONST(AF059,					(GPIO	<< 	22))
    MT_CONST(AF060,					(GPIO	<< 	24))
    MT_CONST(AF061,					(GPIO	<< 	26))
    MT_CONST(AF062,					(GPIO	<< 	28))
    MT_CONST(AF063,					(GPIO	<< 	30))
    MT_CONST(AF064,					(GPIO	<< 	0))
    MT_CONST(AF065,					(GPIO	<< 	2))
    MT_CONST(AF066,					(GPIO	<< 	4))
    MT_CONST(AF067,					(GPIO	<< 	6))
    MT_CONST(AF068,					(GPIO	<< 	8))
    MT_CONST(AF069,					(GPIO	<< 	10))
    MT_CONST(AF070,					(GPIO	<< 	12))
    MT_CONST(AF071,					(GPIO	<< 	14))
    MT_CONST(AF072,					(GPIO	<< 	16))
    MT_CONST(AF073,					(GPIO	<< 	18))
    MT_CONST(AF074,					(GPIO	<< 	20))
    MT_CONST(AF075,					(GPIO	<< 	22))
    MT_CONST(AF076,					(GPIO	<< 	24))
    MT_CONST(AF077,					(GPIO	<< 	26))
    MT_CONST(AF078,					(ALT2	<< 	28))
    MT_CONST(AF079,					(ALT1	<< 	30))
    MT_CONST(AF080,					(ALT2	<< 	0))
    MT_CONST(AF081,					(GPIO	<< 	2))
    MT_CONST(AF082,					(GPIO	<< 	4))
    MT_CONST(AF083,					(ALT3	<< 	6))
    MT_CONST(AF084,					(GPIO	<< 	8))
    MT_CONST(AF085,					(GPIO	<< 	10))
    MT_CONST(AF086,					(GPIO	<< 	12))
    MT_CONST(AF087,					(GPIO	<< 	14))
    MT_CONST(AF088,					(GPIO	<< 	16))
    MT_CONST(AF089,					(GPIO	<< 	18))
    MT_CONST(AF090,					(GPIO	<< 	20))
    MT_CONST(AF091,					(GPIO	<< 	22))
    MT_CONST(AF092,					(GPIO	<< 	24))
    MT_CONST(AF093,					(GPIO	<< 	26))
    MT_CONST(AF094,					(GPIO	<< 	28))
    MT_CONST(AF095,					(GPIO	<< 	30))
    MT_CONST(AF096,					(ALT2	<< 	0))
    MT_CONST(AF097,					(ALT2	<< 	2))
    MT_CONST(AF098,					(GPIO	<< 	4))
    MT_CONST(AF099,					(GPIO	<< 	6))
    MT_CONST(AF100,					(GPIO	<< 	8))
    MT_CONST(AF101,					(GPIO	<< 	10))
    MT_CONST(AF102,					(GPIO	<< 	12))
    MT_CONST(AF103,					(GPIO	<< 	14))
    MT_CONST(AF104,					(GPIO	<< 	16))
    MT_CONST(AF105,					(GPIO	<< 	18))
    MT_CONST(AF106,					(GPIO	<< 	20))
    MT_CONST(AF107,					(GPIO	<< 	22))
    MT_CONST(AF108,					(GPIO	<< 	24))
    MT_CONST(AF109,					(GPIO	<< 	26))
    MT_CONST(AF110,					(GPIO	<< 	28))
    MT_CONST(AF111,					(GPIO	<< 	30))
    MT_CONST(AF112,					(GPIO	<< 	0))
    MT_CONST(AF113,					(GPIO	<< 	2))
    MT_CONST(AF114,					(GPIO	<< 	4))
    MT_CONST(AF115,					(GPIO	<< 	6))
    MT_CONST(AF116,					(GPIO	<< 	8))
    MT_CONST(AF117,					(GPIO	<< 	10))
    MT_CONST(AF118,					(GPIO	<< 	12))
    MT_CONST(AF119,					(GPIO	<< 	14))
    MT_CONST(AF120,					(GPIO	<< 	16))

    MT_CONST(CFG_GAFR0_U_VAL1,		(AF031 | AF030 | AF029 | AF028 | AF027 | AF026 | AF025 | AF024))
    MT_CONST(CFG_GAFR0_U_VAL0,		(AF023 | AF022 | AF021 | AF020 | AF019 | AF018 | AF017 | AF016))
    MT_CONST(CFG_GAFR0_U_VAL	,		(CFG_GAFR0_U_VAL1 | CFG_GAFR0_U_VAL0))
    MT_CONST(CFG_GAFR0_L_VAL1,		(AF015 | AF014 | AF013 | AF012 | AF011 | AF010 | AF009 | AF008))
    MT_CONST(CFG_GAFR0_L_VAL0,		(AF007 | AF006 | AF005 | AF004 | AF003 | AF002 | AF001 | AF000))
    MT_CONST(CFG_GAFR0_L_VAL,		(CFG_GAFR0_L_VAL1 | CFG_GAFR0_L_VAL0))

    MT_CONST(CFG_GAFR1_U_VAL1,		(AF063 | AF062 | AF061 | AF060 | AF059 | AF058 | AF057 | AF056))
    MT_CONST(CFG_GAFR1_U_VAL0,		(AF055 | AF054 | AF053 | AF052 | AF051 | AF050 | AF049 | AF048))
    MT_CONST(CFG_GAFR1_U_VAL,		(CFG_GAFR1_U_VAL1 | CFG_GAFR1_U_VAL0))
    MT_CONST(CFG_GAFR1_L_VAL1,		(AF047 | AF046 | AF045 | AF044 | AF043 | AF042 | AF041 | AF040))
    MT_CONST(CFG_GAFR1_L_VAL0,		(AF039 | AF038 | AF037 | AF036 | AF035 | AF034 | AF033 | AF032))
    MT_CONST(CFG_GAFR1_L_VAL,		(CFG_GAFR1_L_VAL1 | CFG_GAFR1_L_VAL0))

    MT_CONST(CFG_GAFR2_U_VAL1,		(AF095 | AF094 | AF093 | AF092 | AF091 | AF090 | AF089 | AF088))
    MT_CONST(CFG_GAFR2_U_VAL0,		(AF087 | AF086 | AF085 | AF084 | AF083 | AF082 | AF081 | AF080))
    MT_CONST(CFG_GAFR2_U_VAL,		(CFG_GAFR2_U_VAL1 | CFG_GAFR2_U_VAL0))
    MT_CONST(CFG_GAFR2_L_VAL1,		(AF079 | AF078 | AF077 | AF076 | AF075 | AF074 | AF073 | AF072))
    MT_CONST(CFG_GAFR2_L_VAL0,		(AF071 | AF070 | AF069 | AF068 | AF067 | AF066 | AF065 | AF064))
    MT_CONST(CFG_GAFR2_L_VAL,		(CFG_GAFR2_L_VAL1 | CFG_GAFR2_L_VAL0))
	
    MT_CONST(CFG_GAFR3_U_VAL1,		(AF120))
    MT_CONST(CFG_GAFR3_U_VAL0,		(AF119 | AF118 | AF117 | AF116 | AF115 | AF114 | AF113 | AF112))
    MT_CONST(CFG_GAFR3_U_VAL,		(CFG_GAFR3_U_VAL1 | CFG_GAFR3_U_VAL0))
    MT_CONST(CFG_GAFR3_L_VAL1,		(AF111 | AF110 | AF109 | AF108 | AF107 | AF106 | AF105 | AF104))
    MT_CONST(CFG_GAFR3_L_VAL0,		(AF103 | AF102 | AF101 | AF100 | AF099 | AF098 | AF097 | AF096))
    MT_CONST(CFG_GAFR3_L_VAL,		(CFG_GAFR3_L_VAL1 | CFG_GAFR3_L_VAL0))
		
    MT_CONST(DR000,					(GPI	<< 	0))
    MT_CONST(DR001,					(GPI	<< 	1))
    MT_CONST(DR002,					(GPI	<< 	2))
    MT_CONST(DR003,					(GPI	<< 	3))
    MT_CONST(DR004,					(GPI	<< 	4))
    MT_CONST(DR005,					(GPI	<< 	5))
    MT_CONST(DR006,					(GPI	<< 	6))
    MT_CONST(DR007,					(GPI	<< 	7))
    MT_CONST(DR008,					(GPI	<< 	8))
    MT_CONST(DR009,					(GPO	<< 	9))
    MT_CONST(DR010,					(GPI	<< 	10))
    MT_CONST(DR011,					(GPO	<< 	11))
    MT_CONST(DR012,					(GPO	<< 	12))
    MT_CONST(DR013,					(GPO	<< 	13))
    MT_CONST(DR014,					(GPO	<< 	14))
    MT_CONST(DR015,					(GPO	<< 	15))
    MT_CONST(DR016,					(GPO	<< 	16))
    MT_CONST(DR017,					(GPO	<< 	17))
    MT_CONST(DR018,					(GPI	<< 	18))
    MT_CONST(DR019,					(GPO	<< 	19))
    MT_CONST(DR020,					(GPI	<< 	20))
    MT_CONST(DR021,					(GPO	<< 	21))
    MT_CONST(DR022,					(GPO	<< 	22))
    MT_CONST(DR023,					(GPO	<< 	23))
    MT_CONST(DR024,					(GPO	<< 	24))
    MT_CONST(DR025,					(GPO	<< 	25))
    MT_CONST(DR026,					(GPO	<< 	26))
    MT_CONST(DR027,					(GPO	<< 	27))
    MT_CONST(DR028,					(GPO	<< 	28))
    MT_CONST(DR029,					(GPO	<< 	29))
    MT_CONST(DR030,					(GPO	<< 	30))
    MT_CONST(DR031,					(GPO	<< 	31))
    MT_CONST(DR032,					(GPO	<< 	0))
    MT_CONST(DR033,					(GPO	<< 	1))
    MT_CONST(DR034,					(GPO	<< 	2))
    MT_CONST(DR035,					(GPI	<< 	3))
    MT_CONST(DR036,					(GPI	<< 	4))
    MT_CONST(DR037,					(GPI	<< 	5))
    MT_CONST(DR038,					(GPI	<< 	6))
    MT_CONST(DR039,					(GPO	<< 	7))
    MT_CONST(DR040,					(GPO	<< 	8))
    MT_CONST(DR041,					(GPI	<< 	9))
    MT_CONST(DR042,					(GPI	<< 	10))
    MT_CONST(DR043,					(GPO	<< 	11))
    MT_CONST(DR044,					(GPI	<< 	12))
    MT_CONST(DR045,					(GPO	<< 	13))
    MT_CONST(DR046,					(GPO	<< 	14))
    MT_CONST(DR047,					(GPO	<< 	15))
    MT_CONST(DR048,					(GPO	<< 	16))
    MT_CONST(DR049,					(GPO	<< 	17))
    MT_CONST(DR050,					(GPO	<< 	18))
    MT_CONST(DR051,					(GPO	<< 	19))
    MT_CONST(DR052,					(GPO	<< 	20))
    MT_CONST(DR053,					(GPO	<< 	21))
    MT_CONST(DR054,					(GPO	<< 	22))
    MT_CONST(DR055,					(GPO	<< 	23))
    MT_CONST(DR056,					(GPO	<< 	24))
    MT_CONST(DR057,					(GPO	<< 	25))
    MT_CONST(DR058,					(GPO	<< 	26))
    MT_CONST(DR059,					(GPO	<< 	27))
    MT_CONST(DR060,					(GPO	<< 	28))
    MT_CONST(DR061,					(GPO	<< 	29))
	MT_CONST(DR062,					(GPO	<< 	30))
	MT_CONST(DR063,					(GPO	<< 	31))
	MT_CONST(DR064,					(GPO	<< 	0))
	MT_CONST(DR065,					(GPO	<< 	1))
	MT_CONST(DR066,					(GPO	<< 	2))
	MT_CONST(DR067,					(GPO	<< 	3))
	MT_CONST(DR068,					(GPO	<< 	4))
	MT_CONST(DR069,					(GPO	<< 	5))
	MT_CONST(DR070,					(GPO	<< 	6))
	MT_CONST(DR071,					(GPO	<< 	7))
	MT_CONST(DR072,					(GPO	<< 	8))
	MT_CONST(DR073,					(GPO	<< 	9))
	MT_CONST(DR074,					(GPO	<< 	10))
	MT_CONST(DR075,					(GPO	<< 	11))
	MT_CONST(DR076,					(GPO	<< 	12))
	MT_CONST(DR077,					(GPO	<< 	13))
	MT_CONST(DR078,					(GPO	<< 	14))
	MT_CONST(DR079,					(GPO	<< 	15))
	MT_CONST(DR080,					(GPO	<< 	16))
	MT_CONST(DR081,					(GPO	<< 	17))
	MT_CONST(DR082,					(GPO	<< 	18))
	MT_CONST(DR083,					(GPO	<< 	19))
	MT_CONST(DR084,					(GPO	<< 	20))
	MT_CONST(DR085,					(GPO	<< 	21))
	MT_CONST(DR086,					(GPO	<< 	22))
	MT_CONST(DR087,					(GPO	<< 	23))
	MT_CONST(DR088,					(GPI	<< 	24))
	MT_CONST(DR089,					(GPO	<< 	25))
	MT_CONST(DR090,					(GPO	<< 	26))
	MT_CONST(DR091,					(GPO	<< 	27))
	MT_CONST(DR092,					(GPO	<< 	28))
	MT_CONST(DR093,					(GPO	<< 	29))
	MT_CONST(DR094,					(GPO	<< 	30))
	MT_CONST(DR095,					(GPO	<< 	31))
	MT_CONST(DR096,					(GPO	<< 	0))
	MT_CONST(DR097,					(GPI	<< 	1))
	MT_CONST(DR098,					(GPO	<< 	2))
	MT_CONST(DR099,					(GPO	<< 	3))
	MT_CONST(DR100,					(GPO	<< 	4))
	MT_CONST(DR101,					(GPO	<< 	5))
	MT_CONST(DR102,					(GPO	<< 	6))
	MT_CONST(DR103,					(GPO	<< 	7))
	MT_CONST(DR104,					(GPO	<< 	8))
	MT_CONST(DR105,					(GPO	<< 	9))
	MT_CONST(DR106,					(GPO	<< 	10))
	MT_CONST(DR107,					(GPO	<< 	11))
	MT_CONST(DR108,					(GPO	<< 	12))
	MT_CONST(DR109,					(GPO	<< 	13))
	MT_CONST(DR110,					(GPO	<< 	14))
	MT_CONST(DR111,					(GPO	<< 	15))
	MT_CONST(DR112,					(GPO	<< 	16))
	MT_CONST(DR113,					(GPO	<< 	17))
	MT_CONST(DR114,					(GPO	<< 	18))
	MT_CONST(DR115,					(GPO	<< 	19))
	MT_CONST(DR116,					(GPO	<< 	20))
	MT_CONST(DR117,					(GPO	<< 	21))
	MT_CONST(DR118,					(GPO	<< 	22))
	MT_CONST(DR119,					(GPI	<< 	23))
    MT_CONST(DR120,					(GPI	<< 	24))

	MT_CONST(	CFG_GPDR0_VAL3,		(DR031 | DR030 | DR029 | DR028 | DR027 | DR026 | DR025 | DR024))
	MT_CONST(	CFG_GPDR0_VAL2, 	(DR023 | DR022 | DR021 | DR020 | DR019 | DR018 | DR017 | DR016))
	MT_CONST(	CFG_GPDR0_VAL1,		(DR015 | DR014 | DR013 | DR012 | DR011 | DR010 | DR009 | DR008))
	MT_CONST(	CFG_GPDR0_VAL0,		(DR007 | DR006 | DR005 | DR004 | DR003 | DR002 | DR001 | DR000))
	MT_CONST(	CFG_GPDR0_VAL,		(CFG_GPDR0_VAL3 | CFG_GPDR0_VAL2 | CFG_GPDR0_VAL1 | CFG_GPDR0_VAL0))
	MT_CONST(	CFG_GPDR1_VAL3,		(DR063 | DR062 | DR061 | DR060 | DR059 | DR058 | DR057 | DR056))
	MT_CONST(	CFG_GPDR1_VAL2,		(DR055 | DR054 | DR053 | DR052 | DR051 | DR050 | DR049 | DR048))
	MT_CONST(	CFG_GPDR1_VAL1,		(DR047 | DR046 | DR045 | DR044 | DR043 | DR042 | DR041 | DR040))
	MT_CONST(	CFG_GPDR1_VAL0,		(DR039 | DR038 | DR037 | DR036 | DR035 | DR034 | DR033 | DR032))
	MT_CONST(	CFG_GPDR1_VAL,		(CFG_GPDR1_VAL3 | CFG_GPDR1_VAL2 | CFG_GPDR1_VAL1 | CFG_GPDR1_VAL0))
	MT_CONST(	CFG_GPDR2_VAL3,		(DR095 | DR094 | DR093 | DR092 | DR091 | DR090 | DR089 | DR088))
	MT_CONST(	CFG_GPDR2_VAL2,		(DR087 | DR086 | DR085 | DR084 | DR083 | DR082 | DR081 | DR080))
	MT_CONST(	CFG_GPDR2_VAL1,		(DR079 | DR078 | DR077 | DR076 | DR075 | DR074 | DR073 | DR072))
	MT_CONST(	CFG_GPDR2_VAL0,		(DR071 | DR070 | DR069 | DR068 | DR067 | DR066 | DR065 | DR064))
	MT_CONST(	CFG_GPDR2_VAL,		(CFG_GPDR2_VAL3 | CFG_GPDR2_VAL2 | CFG_GPDR2_VAL1 | CFG_GPDR2_VAL0))
	MT_CONST(	CFG_GPDR3_VAL3,		(DR120))
	MT_CONST(	CFG_GPDR3_VAL2, 	(DR119 | DR118 | DR117 | DR116 | DR115 | DR114 | DR113 | DR112))
	MT_CONST(	CFG_GPDR3_VAL1,		(DR111 | DR110 | DR109 | DR108 | DR107 | DR106 | DR105 | DR104))
	MT_CONST(	CFG_GPDR3_VAL0,		(DR103 | DR102 | DR101 | DR100 | DR099 | DR098 | DR097 | DR096))
	MT_CONST(	CFG_GPDR3_VAL,		(CFG_GPDR3_VAL3 | CFG_GPDR3_VAL2 | CFG_GPDR3_VAL1 | CFG_GPDR3_VAL0))


.endif	

    
.ifdef 	NORMAL_TEST

	MT_CONST(AF000,					(GPIO	<< 	0))
	MT_CONST(AF001,					(GPIO	<< 	2))
	MT_CONST(AF002,					(GPIO	<< 	4))
	MT_CONST(AF003,					(GPIO	<< 	6))
	MT_CONST(AF004,					(GPIO	<< 	8))
	MT_CONST(AF005,					(GPIO	<< 	10))
	MT_CONST(AF006,					(GPIO	<< 	12))
	MT_CONST(AF007,					(GPIO	<< 	14))
	MT_CONST(AF008,					(GPIO	<< 	16))
	MT_CONST(AF009,					(GPIO	<< 	18))
	MT_CONST(AF010,					(GPIO	<< 	20))
	MT_CONST(AF011,					(ALT3	<< 	22))
	MT_CONST(AF012,					(GPIO	<< 	24))
	MT_CONST(AF013,					(GPIO	<< 	26))
	MT_CONST(AF014,					(ALT1	<< 	28))
	MT_CONST(AF015,					(ALT2	<< 	30))
	MT_CONST(AF016,					(GPIO	<< 	0))
	MT_CONST(AF017,					(GPIO	<< 	2))
	MT_CONST(AF018,					(ALT1	<< 	4))
	MT_CONST(AF019,					(ALT2	<< 	6))
	MT_CONST(AF020,					(ALT1	<< 	8))
	MT_CONST(AF021,					(ALT2	<< 	10))
	MT_CONST(AF022,					(GPIO	<< 	12))
	MT_CONST(AF023,					(GPIO	<< 	14))
	MT_CONST(AF024,					(GPIO	<< 	16))
	MT_CONST(AF025,					(GPIO	<< 	18))
	MT_CONST(AF026,					(GPIO	<< 	20))
	MT_CONST(AF027,					(GPIO	<< 	22))
	MT_CONST(AF028,					(ALT1	<< 	24))
	MT_CONST(AF029,					(ALT1	<< 	26))
	MT_CONST(AF030,					(ALT2	<< 	28))
	MT_CONST(AF031,					(ALT2	<< 	30))
	MT_CONST(AF032,					(ALT2	<< 	0))
	MT_CONST(AF033,					(ALT2	<< 	2))
	MT_CONST(AF034,					(GPIO	<< 	4))
	MT_CONST(AF035,					(ALT1	<< 	6))
	MT_CONST(AF036,					(ALT1	<< 	8))
	MT_CONST(AF037,					(ALT1	<< 	10))
	MT_CONST(AF038,					(ALT1	<< 	12))
	MT_CONST(AF039,					(ALT2	<< 	14))
	MT_CONST(AF040,					(ALT2	<< 	16))
	MT_CONST(AF041,					(ALT1	<< 	18))
	MT_CONST(AF042,					(ALT1	<< 	20))
	MT_CONST(AF043,					(ALT2	<< 	22))
	MT_CONST(AF044,					(ALT1	<< 	24))
	MT_CONST(AF045,					(ALT2	<< 	26))
	MT_CONST(AF046,					(ALT1	<< 	28))
	MT_CONST(AF047,					(GPIO	<< 	30))
	MT_CONST(AF048,					(ALT2	<< 	0))
	MT_CONST(AF049,					(ALT2	<< 	2))
	MT_CONST(AF050,					(ALT2	<< 	4))
	MT_CONST(AF051,					(ALT2	<< 	6))
	MT_CONST(AF052,					(GPIO	<< 	8))
	MT_CONST(AF053,					(GPIO	<< 	10))
	MT_CONST(AF054,					(ALT2	<< 	12))
	MT_CONST(AF055,					(ALT2	<< 	14))
	MT_CONST(AF056,					(ALT1	<< 	16))
	MT_CONST(AF057,					(ALT1	<< 	18))
	MT_CONST(AF058,					(ALT2	<< 	20))
	MT_CONST(AF059,					(ALT2	<< 	22))
	MT_CONST(AF060,					(ALT2	<< 	24))
	MT_CONST(AF061,					(ALT2	<< 	26))
	MT_CONST(AF062,					(ALT2	<< 	28))
	MT_CONST(AF063,					(ALT2	<< 	30))
	MT_CONST(AF064,					(ALT2	<< 	0))
	MT_CONST(AF065,					(ALT2	<< 	2))
	MT_CONST(AF066,					(ALT2	<< 	4))
	MT_CONST(AF067,					(ALT2	<< 	6))
	MT_CONST(AF068,					(ALT2	<< 	8))
	MT_CONST(AF069,					(ALT2	<< 	10))
	MT_CONST(AF070,					(ALT2	<< 	12))
	MT_CONST(AF071,					(ALT2	<< 	14))
	MT_CONST(AF072,					(ALT2	<< 	16))
	MT_CONST(AF073,					(ALT2	<< 	18))
	MT_CONST(AF074,					(ALT2	<< 	20))
	MT_CONST(AF075,					(ALT2	<< 	22))
	MT_CONST(AF076,					(ALT2	<< 	24))
	MT_CONST(AF077,					(ALT2	<< 	26))
	MT_CONST(AF078,					(ALT2	<< 	28))
	MT_CONST(AF079,					(ALT1	<< 	30))
	MT_CONST(AF080,					(ALT2	<< 	0))
	MT_CONST(AF081,					(GPIO	<< 	2))
	MT_CONST(AF082,					(GPIO	<< 	4))
	MT_CONST(AF083,					(ALT3	<< 	6))
	MT_CONST(AF084,					(GPIO	<< 	8))
	MT_CONST(AF085,					(ALT1	<< 	10))
	MT_CONST(AF086,					(ALT2	<< 	12))
	MT_CONST(AF087,					(ALT2	<< 	14))
	MT_CONST(AF088,					(ALT1	<< 	16))
	MT_CONST(AF089,					(ALT2	<< 	18))
	MT_CONST(AF090,					(GPIO	<< 	20))
	MT_CONST(AF091,					(GPIO	<< 	22))
	MT_CONST(AF092,					(ALT1	<< 	24))
	MT_CONST(AF093,					(GPIO	<< 	26))
	MT_CONST(AF094,					(GPIO	<< 	28))
	MT_CONST(AF095,					(GPIO	<< 	30))
	MT_CONST(AF096,					(ALT2	<< 	0))
	MT_CONST(AF097,					(ALT2	<< 	2))
	MT_CONST(AF098,					(GPIO	<< 	4))
	MT_CONST(AF099,					(GPIO	<< 	6))
	MT_CONST(AF100,					(GPIO	<< 	8))
	MT_CONST(AF101,					(GPIO	<< 	10))
	MT_CONST(AF102,					(GPIO	<< 	12))
	MT_CONST(AF103,					(GPIO	<< 	14))
	MT_CONST(AF104,					(GPIO	<< 	16))
	MT_CONST(AF105,					(GPIO	<< 	18))
	MT_CONST(AF106,					(GPIO	<< 	20))
	MT_CONST(AF107,					(GPIO	<< 	22))
	MT_CONST(AF108,					(GPIO	<< 	24))
	MT_CONST(AF109,					(ALT1	<< 	26))
	MT_CONST(AF110,					(ALT1	<< 	28))
	MT_CONST(AF111,					(ALT1	<< 	30))
	MT_CONST(AF112,					(ALT1	<< 	0))
	MT_CONST(AF113,					(ALT2	<< 	2))
	MT_CONST(AF114,					(GPIO	<< 	4))
	MT_CONST(AF115,					(GPIO	<< 	6))
	MT_CONST(AF116,					(GPIO	<< 	8))
	MT_CONST(AF117,					(ALT1	<< 	10))
	MT_CONST(AF118,					(ALT1	<< 	12))
	MT_CONST(AF119,					(GPIO	<< 	14))
	MT_CONST(AF120,					(GPIO	<< 	16))

	MT_CONST(CFG_GAFR0_U_VAL1,		(AF031 | AF030 | AF029 | AF028 | AF027 | AF026 | AF025 | AF024))
	MT_CONST(CFG_GAFR0_U_VAL0,		(AF023 | AF022 | AF021 | AF020 | AF019 | AF018 | AF017 | AF016))
	MT_CONST(CFG_GAFR0_U_VAL,		(CFG_GAFR0_U_VAL1 | CFG_GAFR0_U_VAL0))
	MT_CONST(CFG_GAFR0_L_VAL1,		(AF015 | AF014 | AF013 | AF012 | AF011 | AF010 | AF009 | AF008))
	MT_CONST(CFG_GAFR0_L_VAL0,		(AF007 | AF006 | AF005 | AF004 | AF003 | AF002 | AF001 | AF000))
	MT_CONST(CFG_GAFR0_L_VAL,		(CFG_GAFR0_L_VAL1 | CFG_GAFR0_L_VAL0))
		
	MT_CONST(CFG_GAFR1_U_VAL1,		(AF063 | AF062 | AF061 | AF060 | AF059 | AF058 | AF057 | AF056))
	MT_CONST(CFG_GAFR1_U_VAL0,		(AF055 | AF054 | AF053 | AF052 | AF051 | AF050 | AF049 | AF048))
	MT_CONST(CFG_GAFR1_U_VAL,		(CFG_GAFR1_U_VAL1 | CFG_GAFR1_U_VAL0))
	MT_CONST(CFG_GAFR1_L_VAL1,		(AF047 | AF046 | AF045 | AF044 | AF043 | AF042 | AF041 | AF040))
	MT_CONST(CFG_GAFR1_L_VAL0,		(AF039 | AF038 | AF037 | AF036 | AF035 | AF034 | AF033 | AF032))
	MT_CONST(CFG_GAFR1_L_VAL,		(CFG_GAFR1_L_VAL1 | CFG_GAFR1_L_VAL0))

	MT_CONST(CFG_GAFR2_U_VAL1,		(AF095 | AF094 | AF093 | AF092 | AF091 | AF090 | AF089 | AF088))
	MT_CONST(CFG_GAFR2_U_VAL0,		(AF087 | AF086 | AF085 | AF084 | AF083 | AF082 | AF081 | AF080))
	MT_CONST(CFG_GAFR2_U_VAL,		(CFG_GAFR2_U_VAL1 | CFG_GAFR2_U_VAL0))
	MT_CONST(CFG_GAFR2_L_VAL1,		(AF079 | AF078 | AF077 | AF076 | AF075 | AF074 | AF073 | AF072))
	MT_CONST(CFG_GAFR2_L_VAL0,		(AF071 | AF070 | AF069 | AF068 | AF067 | AF066 | AF065 | AF064))
	MT_CONST(CFG_GAFR2_L_VAL,		(CFG_GAFR2_L_VAL1 | CFG_GAFR2_L_VAL0))

	MT_CONST(CFG_GAFR3_U_VAL1,		(AF120))
	MT_CONST(CFG_GAFR3_U_VAL0,		(AF119 | AF118 | AF117 | AF116 | AF115 | AF114 | AF113 | AF112))
	MT_CONST(CFG_GAFR3_U_VAL,		(CFG_GAFR3_U_VAL1 | CFG_GAFR3_U_VAL0))
	MT_CONST(CFG_GAFR3_L_VAL1,		(AF111 | AF110 | AF109 | AF108 | AF107 | AF106 | AF105 | AF104))
	MT_CONST(CFG_GAFR3_L_VAL0,		(AF103 | AF102 | AF101 | AF100 | AF099 | AF098 | AF097 | AF096))
	MT_CONST(CFG_GAFR3_L_VAL,		(CFG_GAFR3_L_VAL1 | CFG_GAFR3_L_VAL0))

	MT_CONST(DR000,					(GPI	<< 	0))
	MT_CONST(DR001,					(GPI	<< 	1))
	MT_CONST(DR002,					(GPI	<< 	2))
	MT_CONST(DR003,					(GPI	<< 	3))
	MT_CONST(DR004,					(GPI	<< 	4))
	MT_CONST(DR005,					(GPI	<< 	5))
	MT_CONST(DR006,					(GPI	<< 	6))
	MT_CONST(DR007,					(GPI	<< 	7))
	MT_CONST(DR008,					(GPI	<< 	8))
	MT_CONST(DR009,					(GPO	<< 	9))
	MT_CONST(DR010,					(GPI	<< 	10))
	MT_CONST(DR011,					(GPO	<< 	11))
	MT_CONST(DR012,					(GPI	<< 	12))
	MT_CONST(DR013,					(GPI	<< 	13))
	MT_CONST(DR014,					(GPI	<< 	14))
	MT_CONST(DR015,					(GPO	<< 	15))
	MT_CONST(DR016,					(GPI	<< 	16))
	MT_CONST(DR017,					(GPI	<< 	17))
	MT_CONST(DR018,					(GPI	<< 	18))
	MT_CONST(DR019,					(GPO	<< 	19))
	MT_CONST(DR020,					(GPI	<< 	20))
	MT_CONST(DR021,					(GPO	<< 	21))
	MT_CONST(DR022,					(GPI	<< 	22))
	MT_CONST(DR023,					(GPI	<< 	23))
	MT_CONST(DR024,					(GPI	<< 	24))
	MT_CONST(DR025,					(GPI	<< 	25))
	MT_CONST(DR026,					(GPI	<< 	26))
	MT_CONST(DR027,					(GPI	<< 	27))
	MT_CONST(DR028,					(GPI	<< 	28))
	MT_CONST(DR029,					(GPI	<< 	29))
	MT_CONST(DR030,					(GPO	<< 	30))
	MT_CONST(DR031,					(GPO	<< 	31))
	MT_CONST(DR032,					(GPO	<< 	0))
	MT_CONST(DR033,					(GPO	<< 	1))
	MT_CONST(DR034,					(GPI	<< 	2))
	MT_CONST(DR035,					(GPI	<< 	3))
	MT_CONST(DR036,					(GPI	<< 	4))
	MT_CONST(DR037,					(GPI	<< 	5))
	MT_CONST(DR038,					(GPI	<< 	6))
	MT_CONST(DR039,					(GPO	<< 	7))
	MT_CONST(DR040,					(GPO	<< 	8))
	MT_CONST(DR041,					(GPI	<< 	9))
	MT_CONST(DR042,					(GPI	<< 	10))
	MT_CONST(DR043,					(GPO	<< 	11))
	MT_CONST(DR044,					(GPI	<< 	12))
	MT_CONST(DR045,					(GPO	<< 	13))
	MT_CONST(DR046,					(GPI	<< 	14))
	MT_CONST(DR047,					(GPI	<< 	15))
	MT_CONST(DR048,					(GPO	<< 	16))
	MT_CONST(DR049,					(GPO	<< 	17))
	MT_CONST(DR050,					(GPO	<< 	18))
	MT_CONST(DR051,					(GPO	<< 	19))
	MT_CONST(DR052,					(GPI	<< 	20))
	MT_CONST(DR053,					(GPO	<< 	21))
	MT_CONST(DR054,					(GPO	<< 	22))
	MT_CONST(DR055,					(GPO	<< 	23))
	MT_CONST(DR056,					(GPI	<< 	24))
	MT_CONST(DR057,					(GPI	<< 	25))
	MT_CONST(DR058,					(GPI	<< 	26))
	MT_CONST(DR059,					(GPI	<< 	27))
	MT_CONST(DR060,					(GPI	<< 	28))
	MT_CONST(DR061,					(GPI	<< 	29))
	MT_CONST(DR062,					(GPI	<< 	30))
	MT_CONST(DR063,					(GPI	<< 	31))
	MT_CONST(DR064,					(GPI	<< 	0))
	MT_CONST(DR065,					(GPI	<< 	1))
	MT_CONST(DR066,					(GPI	<< 	2))
	MT_CONST(DR067,					(GPI	<< 	3))
	MT_CONST(DR068,					(GPI	<< 	4))
	MT_CONST(DR069,					(GPI	<< 	5))
	MT_CONST(DR070,					(GPI	<< 	6))
	MT_CONST(DR071,					(GPI	<< 	7))
	MT_CONST(DR072,					(GPI	<< 	8))
	MT_CONST(DR073,					(GPI	<< 	9))
	MT_CONST(DR074,					(GPO	<< 	10))
	MT_CONST(DR075,					(GPO	<< 	11))
	MT_CONST(DR076,					(GPO	<< 	12))
	MT_CONST(DR077,					(GPO	<< 	13))
	MT_CONST(DR078,					(GPO	<< 	14))
	MT_CONST(DR079,					(GPO	<< 	15))
	MT_CONST(DR080,					(GPO	<< 	16))
	MT_CONST(DR081,					(GPI	<< 	17))
	MT_CONST(DR082,					(GPI	<< 	18))
	MT_CONST(DR083,					(GPO	<< 	19))
	MT_CONST(DR084,					(GPI	<< 	20))
	MT_CONST(DR085,					(GPO	<< 	21))
	MT_CONST(DR086,					(GPI	<< 	22))
	MT_CONST(DR087,					(GPI	<< 	23))
	MT_CONST(DR088,					(GPI	<< 	24))
	MT_CONST(DR089,					(GPO	<< 	25))
	MT_CONST(DR090,					(GPI	<< 	26))
	MT_CONST(DR091,					(GPI	<< 	27))
	MT_CONST(DR092,					(GPI	<< 	28))
	MT_CONST(DR093,					(GPI	<< 	29))
	MT_CONST(DR094,					(GPI	<< 	30))
	MT_CONST(DR095,					(GPI	<< 	31))
	MT_CONST(DR096,					(GPO	<< 	0))
	MT_CONST(DR097,					(GPI	<< 	1))
	MT_CONST(DR098,					(GPI	<< 	2))
	MT_CONST(DR099,					(GPI	<< 	3))
	MT_CONST(DR100,					(GPI	<< 	4))
	MT_CONST(DR101,					(GPI	<< 	5))
	MT_CONST(DR102,					(GPI	<< 	6))
	MT_CONST(DR103,					(GPI	<< 	7))
	MT_CONST(DR104,					(GPI	<< 	8))
	MT_CONST(DR105,					(GPI	<< 	9))
	MT_CONST(DR106,					(GPI	<< 	10))
	MT_CONST(DR107,					(GPI	<< 	11))
	MT_CONST(DR108,					(GPI	<< 	12))
	MT_CONST(DR109,					(GPI	<< 	13))
	MT_CONST(DR110,					(GPI	<< 	14))
	MT_CONST(DR111,					(GPI	<< 	15))
	MT_CONST(DR112,					(GPI	<< 	16))
	MT_CONST(DR113,					(GPO	<< 	17))
	MT_CONST(DR114,					(GPI	<< 	18))
	MT_CONST(DR115,					(GPI	<< 	19))
	MT_CONST(DR116,					(GPI	<< 	20))
	MT_CONST(DR117,					(GPI	<< 	21))
	MT_CONST(DR118,					(GPI	<< 	22))
	MT_CONST(DR119,					(GPI	<< 	23))
	MT_CONST(DR120,					(GPI	<< 	24))

	MT_CONST(CFG_GPDR0_VAL3,		(DR031 | DR030 | DR029 | DR028 | DR027 | DR026 | DR025 | DR024))
	MT_CONST(CFG_GPDR0_VAL2,		(DR023 | DR022 | DR021 | DR020 | DR019 | DR018 | DR017 | DR016))
	MT_CONST(CFG_GPDR0_VAL1,		(DR015 | DR014 | DR013 | DR012 | DR011 | DR010 | DR009 | DR008))
	MT_CONST(CFG_GPDR0_VAL0,		(DR007 | DR006 | DR005 | DR004 | DR003 | DR002 | DR001 | DR000))
	MT_CONST(CFG_GPDR0_VAL,		    (CFG_GPDR0_VAL3 | CFG_GPDR0_VAL2 | CFG_GPDR0_VAL1 | CFG_GPDR0_VAL0))
	MT_CONST(CFG_GPDR1_VAL3,		(DR063 | DR062 | DR061 | DR060 | DR059 | DR058 | DR057 | DR056))
	MT_CONST(CFG_GPDR1_VAL2,		(DR055 | DR054 | DR053 | DR052 | DR051 | DR050 | DR049 | DR048))
	MT_CONST(CFG_GPDR1_VAL1,		(DR047 | DR046 | DR045 | DR044 | DR043 | DR042 | DR041 | DR040))
	MT_CONST(CFG_GPDR1_VAL0,		(DR039 | DR038 | DR037 | DR036 | DR035 | DR034 | DR033 | DR032))
	MT_CONST(CFG_GPDR1_VAL,		    (CFG_GPDR1_VAL3 | CFG_GPDR1_VAL2 | CFG_GPDR1_VAL1 | CFG_GPDR1_VAL0))
	MT_CONST(CFG_GPDR2_VAL3,		(DR095 | DR094 | DR093 | DR092 | DR091 | DR090 | DR089 | DR088))
	MT_CONST(CFG_GPDR2_VAL2,		(DR087 | DR086 | DR085 | DR084 | DR083 | DR082 | DR081 | DR080))
	MT_CONST(CFG_GPDR2_VAL1,		(DR079 | DR078 | DR077 | DR076 | DR075 | DR074 | DR073 | DR072))
	MT_CONST(CFG_GPDR2_VAL0,		(DR071 | DR070 | DR069 | DR068 | DR067 | DR066 | DR065 | DR064))
	MT_CONST(CFG_GPDR2_VAL,		    (CFG_GPDR2_VAL3 | CFG_GPDR2_VAL2 | CFG_GPDR2_VAL1 | CFG_GPDR2_VAL0))
	MT_CONST(CFG_GPDR3_VAL3,		(DR120))
	MT_CONST(CFG_GPDR3_VAL2,		(DR119 | DR118 | DR117 | DR116 | DR115 | DR114 | DR113 | DR112))
	MT_CONST(CFG_GPDR3_VAL1,		(DR111 | DR110 | DR109 | DR108 | DR107 | DR106 | DR105 | DR104))
	MT_CONST(CFG_GPDR3_VAL0,		(DR103 | DR102 | DR101 | DR100 | DR099 | DR098 | DR097 | DR096))
	MT_CONST(CFG_GPDR3_VAL,		    (CFG_GPDR3_VAL3 | CFG_GPDR3_VAL2 | CFG_GPDR3_VAL1 | CFG_GPDR3_VAL0))

.endif

	/*===========================================================
     * ;;;;;;;;;;	Interrupt Ddefination	;;;;;;;;;
     *==========================================================*/
	MT_CONST(IC_BASE,               0x40D00000)
	MT_CONST(ICMR_OFFSET,			0x04)
	MT_CONST(ICLR_OFFSET,			0x08)

	/*===========================================================
     * ;;;;;;;;;;	CLK Ddefination	;;;;;;;;;
     *==========================================================*/
	MT_CONST(CC_BASE,	            0x41300000)
	MT_CONST(CCCR_OFFSET,			0x00)
	MT_CONST(CKEN_OFFSET,			0x04)

.ifdef 	CPU_520MHZ
	MT_CONST(CCCR_VALUE,			0x00000290)
	
	/*===========================================================
     * ;;;;;	RUN = 208M, TURBO = 520M, SYSTEM_BUS==208M, CLK_MEM=104M, SDCLK=104M, SFLASH=52M, LCD=104M
     * ==========================================================*/
	MT_CONST(CLKCFG_VALUE,			0xb)
.else
	MT_CONST(CCCR_VALUE,			0x00000190)

	/*===========================================================
     * ;;;;;	RUN = 208M, TURBO = 312M, SYSTEM_BUS==104M, CLK_MEM=104M, SDCLK=104M, SFLASH=52M, LCD=104M
     *==========================================================*/
	MT_CONST(CLKCFG_VALUE,			0xb)	
.endif

	MT_CONST(PSSR,			        0x40F00004)

	/*===========================================================
     * ;;;;;;;;;;	MEMC Ddefination	;;;;;;;;;
     *==========================================================*/
	MT_CONST(MEMC_BASE,		        0x48000000)

	/*===========================================================
     *;;;;;	nCS0 = FLASH-16				OE=RDF0+2-1,	WE=RDN0+1,	CS(R/W)=OE/WE+2+1
     *;;;;;					TEST RESULT	OE=90n			WE=90n(?60)	CS(R/W)=90n/120n(?90)
     *==========================================================*/     
	MT_CONST(MCS0_RT0,				0)			/* FLASH                    */
	MT_CONST(MCS0_RBW0,				1)			/* BW = 16 BITS             */
	MT_CONST(MCS0_RDF0,				8)			/*cycle time of RD = (8+2CLK_MEM:1'st acc) or (8+1CLK_MEM:others)*/
	MT_CONST(MCS0_RDN0,				5)			/* cycle time of WE = 5+1 CLK_MEM */
	MT_CONST(MCS0_RRR0,				1)			/* CS Recovery time = (1 * 2 + 1) CLK_MEM */
	MT_CONST(MCS0_RBUFF0,			0)			/* Slower device            */
	MT_CONST(MCS0_VALUE1,			(MCS0_RBUFF0<<15 |  MCS0_RRR0<<12 | MCS0_RDN0<<8 | MCS0_RDF0<<4 | MCS0_RBW0<<3 | MCS0_RT0))
;	MT_CONST(MCS0_VALUE1,			(0x7ff8))
	
	/*===========================================================	
     * ;;;;;	nCS1 = ETHERNET-32			OE=RDF1+1+wait,	nPWE=OE,	CS(R/W)=OE+2+1
     * ;;;;;					TEST RESULT	OE=40n			nPWE=40n	CS(R/W)=70n
     *==========================================================*/
	MT_CONST(MCS0_RT1,				4)			/* VLIO                                   */
	MT_CONST(MCS0_RBW1,				0)			/* BW = 32 BITS                           */
	MT_CONST(MCS0_RDF1,				3)			/* cycle time of RD/WE                    */
	MT_CONST(MCS0_RDN1,				2)			/* nPWE/nOE deasserted period = RDN * 2   */
	MT_CONST(MCS0_RRR1,				1)			/* CS Recovery time = (1 * 2 + 1) CLK_MEM */ 
	MT_CONST(MCS0_RBUFF1,			0)			/* Slower device                          */
	MT_CONST(MCS0_VALUE2,			(MCS0_RBUFF1<<15 |  MCS0_RRR1<<12 | MCS0_RDN1<<8 | MCS0_RDF1<<4 | MCS0_RBW1<<3 | MCS0_RT1))
	MT_CONST(MCS0_VALUE,			(MCS0_VALUE2 << 16 | MCS0_VALUE1))

	/*===========================================================
     * ;;;;;	nCS2 = Creator_IO-16		OE=RDF2+1+wait,	nPWE=OE,	CS(R/W)=OE+2+1
     * ;;;;;					TEST RESULT	OE=120n			nPWE=120n	CS(R/W)=150n
     *==========================================================*/     
	MT_CONST(MCS1_RT2,				4)			/* VLIO                                    */
	MT_CONST(MCS1_RBW2,				1)			/* BW = 16 BITS                            */
	MT_CONST(MCS1_RDF2,				12)			/* (11)cycle time of RD/WE (setup to 120ns)*/
	MT_CONST(MCS1_RDN2,				2)			/* (2)nPWE/nOE deasserted period = RDN * 2 */
	MT_CONST(MCS1_RRR2,				1)			/* CS Recovery time = (1 * 2 + 1) CLK_MEM  */
	MT_CONST(MCS1_RBUFF2,			0)			/* Slower device                           */
	MT_CONST(MCS1_VALUE1,			(MCS1_RBUFF2<<15 |  MCS1_RRR2<<12 | MCS1_RDN2<<8 | MCS1_RDF2<<4 | MCS1_RBW2<<3 | MCS1_RT2))
	MT_CONST(MCS1_VALUE2,			(0x0000))
	MT_CONST(MCS1_VALUE,			(MCS1_VALUE2 << 16 | MCS1_VALUE1))

	/*===========================================================
     * ;;;;;	nCS4 = SRAM-16				OE=RDF4+2-1,	WE=RDN4+1,	CS(R/W)=OE/WE+2+1
     * ;;;;;					TEST RESULT	OE=60n			WE=40n		CS(R/W)=60n/70n
     *==========================================================*/
	MT_CONST(MCS2_RT4,				1)			/* SRAM             */
	MT_CONST(MCS2_RBW4,				1)			/* BW = 16 BITS     */
	MT_CONST(MCS2_RDF4,				5)			/* cycle time of RD = (5+2CLK_MEM:1'st acc) or (5+1CLK_MEM:others) */
	MT_CONST(MCS2_RDN4,				3)			/* cycle time of WE = 3+1 CLK_MEM          */
	MT_CONST(MCS2_RRR4,				1)			/* CS Recovery time = (1 * 2 + 1) CLK_MEM  */
	MT_CONST(MCS2_RBUFF4,			0)			/* Slower device                           */
	MT_CONST(MCS2_VALUE1,			(MCS2_RBUFF4<<15 |  MCS2_RRR4<<12 | MCS2_RDN4<<8 | MCS2_RDF4<<4 | MCS2_RBW4<<3 | MCS2_RT4))

	/*===========================================================
     * ;;;;;	nCS5 = Creator_IO-16-0WAIT	OE=RDF5+2-1,	WE=RDN5+1,	CS(R/W)=OE/WE+2+1
     * ;;;;;					TEST RESULT	OE=60n			WE=40n		CS(R/W)=60n/70n
     *==========================================================*/     
	MT_CONST(MCS2_RT5,				1)			/* SRAM                                    */
	MT_CONST(MCS2_RBW5,				1)			/* BW = 16 BITS                            */
	MT_CONST(MCS2_RDF5,				5)			/* cycle time of RD = (5+2CLK_MEM:1'st acc) or (5+1CLK_MEM:others) */
	MT_CONST(MCS2_RDN5,				3)			/* cycle time of WE = 3+1 CLK_MEM          */
	MT_CONST(MCS2_RRR5,				1)			/* CS Recovery time = (1 * 2 + 1) CLK_MEM  */
	MT_CONST(MCS2_RBUFF5,			0)			/* Slower device                           */
	MT_CONST(MCS2_VALUE2,			(MCS2_RBUFF5<<15 |  MCS2_RRR5<<12 | MCS2_RDN5<<8 | MCS2_RDF5<<4 | MCS2_RBW5<<3 | MCS2_RT5))
	MT_CONST(MCS2_VALUE,			(MCS2_VALUE2 << 16 | MCS2_VALUE1))


	MT_CONST(MDCNFG_OFFSET,       0x0)
	MT_CONST(MDREFR_OFFSET,       0x4)
	MT_CONST(MSC0_OFFSET,         0x8)
	MT_CONST(MSC1_OFFSET,         0xC)
	MT_CONST(MSC2_OFFSET,         0x10)
	MT_CONST(MECR_OFFSET,         0x14)
	MT_CONST(SXLCR_OFFSET,        0x18)
	MT_CONST(SXCNFG_OFFSET,       0x1C)
	MT_CONST(FLYCNFG_OFFSET,      0x20)
	MT_CONST(SXMRS_OFFSET,        0x24)
	MT_CONST(MCMEM0_OFFSET,       0x28)
	MT_CONST(MCMEM1_OFFSET,       0x2C)
	MT_CONST(MCATT0_OFFSET,       0x30)
	MT_CONST(MCATT1_OFFSET,       0x34)
	MT_CONST(MCIO0_OFFSET,        0x38)
	MT_CONST(MCIO1_OFFSET,        0x3C)
	MT_CONST(MDMRS_OFFSET,        0x40)

	MT_CONST(MDREFR_K0DB4,       (1 << 29))
	MT_CONST(MDREFR_K2FREE,	     (1 << 25))
	MT_CONST(MDREFR_K1FREE,	     (1 << 24))
	MT_CONST(MDREFR_K0FREE,	     (1 << 23))
	MT_CONST(MDREFR_SLFRSH,	     (1 << 22))
	MT_CONST(MDREFR_APD,		 (1 << 20))
	MT_CONST(MDREFR_K2DB2,	     (1 << 19))
	MT_CONST(MDREFR_K2RUN,	     (1 << 18))
	MT_CONST(MDREFR_K1DB2,	     (1 << 17))
	MT_CONST(MDREFR_K1RUN,	     (1 << 16))
	MT_CONST(MDREFR_E1PIN,	     (1 << 15))
	MT_CONST(MDREFR_K0DB2,	     (1 << 14))
	MT_CONST(MDREFR_K0RUN,	     (1 << 13))
	MT_CONST(MDREFR_E0PIN,	     (1 << 12))



	MT_CONST(MCMEM0_SET,		 (4-2))	/* 36ns  */
	MT_CONST(MCMEM0_ASST,	     (3))	/* 150ns */
	MT_CONST(MCMEM0_HOLD,	     (4))	/* 36ns  */
	MT_CONST(MCATT0_SET,		 (4-2))	/* 36ns  */
	MT_CONST(MCATT0_ASST,	     (8))	/* 300ns */
	MT_CONST(MCATT0_HOLD,	     (4))	/* 36ns  */
	MT_CONST(MCIO0_SET,	         (8-2))	/* 72ns  */
	MT_CONST(MCIO0_ASST,	     (4))	/* 180ns */
	MT_CONST(MCIO0_HOLD,	     (4))	/* 36ns  */
	MT_CONST(CFG_MECR_VAL,		  0)
	MT_CONST(CFG_MCMEM0_VAL,	 ((MCMEM0_HOLD << 14) | (MCMEM0_ASST << 7) | (MCMEM0_SET)))
	MT_CONST(CFG_MCMEM1_VAL,	 0xfffff)
	MT_CONST(CFG_MCATT0_VAL,	 ((MCATT0_HOLD << 14) | (MCATT0_ASST << 7) | (MCATT0_SET)))
	MT_CONST(CFG_MCATT1_VAL,	 0xfffff)
	MT_CONST(CFG_MCIO0_VAL,		 ((MCIO0_HOLD << 14) | (MCIO0_ASST << 7) | (MCIO0_SET)))
	MT_CONST(CFG_MCIO1_VAL,		 0xfffff)

	/*===========================================================
     * Pre-defined constants
     *==========================================================*/     
	MT_CONST(USER_MODE,           0x10)
	MT_CONST(FIQ_MODE,            0x11)
	MT_CONST(IRQ_MODE,            0x12)
	MT_CONST(SVC_MODE,            0x13)
	MT_CONST(ABORT_MODE,          0x17)
	MT_CONST(UNDEF_MODE,          0x1b)
	MT_CONST(MODE_MASK ,          0x1f)
	MT_CONST(NOINT,               0xc0)


/*
	MT_CONST(IRAM_BASE,  		  0x5C010000)

	MT_CONST(_CSTACK,             IRAM_BASE)
	MT_CONST(_IRQ_STACK,		  _CSTACK-0x1000)
	MT_CONST(_FIQ_STACK,		  _IRQ_STACK-0x1000)
*/	


	MT_CONST(ROM0_SIZE, 		  0x200000)
	MT_CONST(SDRAM0_BASE_FOR_LOADER	, 0x1000000)