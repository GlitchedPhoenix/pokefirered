#include "global.h"
#include "gflib.h"
#include "scanline_effect.h"
#include "text_window_graphics.h"
#include "new_menu_helpers.h"
#include "menu.h"
#include "task.h"
#include "overworld.h"
#include "help_system.h"
#include "text_window.h"
#include "strings.h"
#include "field_fadetransition.h"
#include "gba/m4a_internal.h"

#define tMenuSelection data[0]
#define tTextSpeed data[1]
#define tBattleSceneOff data[2]
#define tBattleStyle data[3]
#define tSound data[4]
#define tButtonMode data[5]
#define tWindowFrameType data[6]
#define tQuickNurse data[7]
#define tPermaRun data[8]
#define tQuickContinue data[9]
#define tExpAll data[10]

#define PAGE_COUNT  2

// can't include the one in menu_helpers.h since Task_OptionMenu needs bool32 for matching
bool32 IsActiveOverworldLinkBusy(void);

// Menu items
enum
{
    MENUITEM_TEXTSPEED = 0,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_NEXT,
    MENUITEM_COUNT
};

enum
{
    MENUITEM_QUICKNURSE,
    MENUITEM_PERMARUN,
    MENUITEM_QUICKCONTINUE,
	MENUITEM_EXPALL,
    MENUITEM_BACK,
    MENUITEM_COUNT_2
};

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

// RAM symbols
struct OptionMenu
{
    /*0x00*/ u16 option[MENUITEM_COUNT];
    /*0x0E*/ u16 cursorPos;
    /*0x10*/ u8 loadState;
    /*0x11*/ u8 state;
    /*0x12*/ u8 loadPaletteState;
};

static EWRAM_DATA struct OptionMenu *sOptionMenuPtr = NULL;
EWRAM_DATA static u8 sCurrPage = 0;

//Function Declarataions
static void CB2_InitOptionMenu(void);
static void VBlankCB_OptionMenu(void);
static void OptionMenu_InitCallbacks(void);
static void OptionMenu_SetVBlankCallback(void);
static void CB2_OptionMenu(void);
static void SetOptionMenuTask(void);
static void InitOptionMenuBg(void);
static void OptionMenu_PickSwitchCancel(void);
static void Task_ChangePage(u8 taskId);
static void OptionMenu_ResetSpriteData(void);
static bool8 LoadOptionMenuPalette(void);
static void Task_OptionMenu(u8 taskId);
static u8 OptionMenu_ProcessInput(u8 taskId);
static void BufferOptionMenuString(u8 selection);
static void BufferOptionMenuString2(u8 selection);
static void CloseAndSaveOptionMenu(u8 taskId);
static void PrintOptionMenuHeader(void);
static void DrawOptionMenuBg(void);
static void LoadOptionMenuItemNames(void);
static void UpdateSettingSelectionDisplay(u16 selection);

// Data Definitions
static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 7,
        .width = 26,
        .height = 12,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x16e
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 2,
       .charBaseIndex = 1,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
       .baseTile = 0
   },
};

static const u16 sOptionMenuPalette[] = INCBIN_U16("graphics/misc/option_menu.gbapal");
static const u16 sOptionMenuItemCounts[MENUITEM_COUNT] = {3, 2, 2, 2, 3, 10, 0};
static const u16 sOptionMenuItemCounts2[MENUITEM_COUNT] = {2, 2, 2, 2, 0};

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_NEXT]      = gText_OptionMenuNext,
};

static const u8 *const sOptionMenuItemsNames_Pg2[MENUITEM_COUNT_2] =
{
    [MENUITEM_QUICKNURSE]          = gText_Nurse,
    [MENUITEM_PERMARUN]            = gText_AlwaysRun,
    [MENUITEM_QUICKCONTINUE]       = gText_Continue,
	[MENUITEM_EXPALL]       = gText_ExpAll,
    [MENUITEM_BACK]                = gText_OptionMenuBack
};

static const u8 *const sContinueNames[] =
{
    gText_Default,
    gText_Menu,
};

static const u8 *const sQuickNurseOptions[] =
{
    gText_Normal,
    gText_Quick2,
};

static const u8 *const sTextSpeedOptions[] =
{
    gText_TextSpeedSlow, 
    gText_TextSpeedMid, 
    gText_TextSpeedFast
};

static const u8 *const sBattleSceneOptions[] =
{
    gText_BattleSceneOn, 
    gText_BattleSceneOff
};

static const u8 *const sPermaRunOptions[] =
{
    gText_BattleSceneOff, 
    gText_BattleSceneOn
};

static const u8 *const sBattleStyleOptions[] =
{
    gText_BattleStyleShift,
    gText_BattleStyleSet
};

static const u8 *const sSoundOptions[] =
{
    gText_SoundMono, 
    gText_SoundStereo
};

static const u8 *const sButtonTypeOptions[] =
{
    gText_ButtonTypeHelp,
	gText_ButtonTypeLR,
	gText_ButtonTypeLEqualsA
};

static const u8 sOptionMenuPickSwitchCancelTextColor[] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sOptionMenuTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED};

// Functions
static void CB2_InitOptionMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_OptionMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void ReadAllCurrentSettings(u8 taskId)
{
    gTasks[taskId].tMenuSelection = 0;
	gTasks[taskId].tTextSpeed = gSaveBlock2Ptr->optionsTextSpeed;
	gTasks[taskId].tBattleSceneOff = gSaveBlock2Ptr->optionsBattleSceneOff;
	gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
	gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
	gTasks[taskId].tButtonMode = gSaveBlock2Ptr->optionsButtonMode;
	gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
	gTasks[taskId].tQuickNurse = gSaveBlock2Ptr->quickNurse;
	gTasks[taskId].tPermaRun = gSaveBlock2Ptr->permaRun;
	gTasks[taskId].tQuickContinue = gSaveBlock2Ptr->quickContinue;
	gTasks[taskId].tExpAll = gSaveBlock2Ptr->expAll;
}

static void HandlePageSettings(u8 taskId)
{
	if (sCurrPage == 1)
	{
		gTasks[taskId].tTextSpeed = sOptionMenuPtr->option[MENUITEM_TEXTSPEED];
		gTasks[taskId].tBattleSceneOff = sOptionMenuPtr->option[MENUITEM_BATTLESCENE];
		gTasks[taskId].tBattleStyle = sOptionMenuPtr->option[MENUITEM_BATTLESTYLE];
		gTasks[taskId].tSound = sOptionMenuPtr->option[MENUITEM_SOUND];
		gTasks[taskId].tButtonMode = sOptionMenuPtr->option[MENUITEM_BUTTONMODE];
		gTasks[taskId].tWindowFrameType = sOptionMenuPtr->option[MENUITEM_FRAMETYPE];
		
		sOptionMenuPtr->option[MENUITEM_QUICKNURSE] = gTasks[taskId].tQuickNurse;
		sOptionMenuPtr->option[MENUITEM_PERMARUN] = gTasks[taskId].tPermaRun;
		sOptionMenuPtr->option[MENUITEM_QUICKCONTINUE] = gTasks[taskId].tQuickContinue;
		sOptionMenuPtr->option[MENUITEM_EXPALL] = gTasks[taskId].tExpAll;
	}
	else
	{
		gTasks[taskId].tQuickNurse = sOptionMenuPtr->option[MENUITEM_QUICKNURSE];
		gTasks[taskId].tPermaRun = sOptionMenuPtr->option[MENUITEM_PERMARUN];
		gTasks[taskId].tQuickContinue = sOptionMenuPtr->option[MENUITEM_QUICKCONTINUE];
		gTasks[taskId].tExpAll = sOptionMenuPtr->option[MENUITEM_EXPALL];
		
		sOptionMenuPtr->option[MENUITEM_TEXTSPEED] = gTasks[taskId].tTextSpeed;
		sOptionMenuPtr->option[MENUITEM_BATTLESCENE] = gTasks[taskId].tBattleSceneOff;
		sOptionMenuPtr->option[MENUITEM_BATTLESTYLE] = gTasks[taskId].tBattleStyle;
		sOptionMenuPtr->option[MENUITEM_SOUND] = gTasks[taskId].tSound;
		sOptionMenuPtr->option[MENUITEM_BUTTONMODE] = gTasks[taskId].tButtonMode;
		sOptionMenuPtr->option[MENUITEM_FRAMETYPE] = gTasks[taskId].tWindowFrameType;
	}
}

void CB2_OptionsMenuFromStartMenu(void)
{
    u8 i;
    
    if (gMain.savedCallback == NULL)
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
    sOptionMenuPtr = AllocZeroed(sizeof(struct OptionMenu));
    sOptionMenuPtr->loadState = 0;
    sOptionMenuPtr->loadPaletteState = 0;
    sOptionMenuPtr->state = 0;
    sOptionMenuPtr->cursorPos = 0;
    sOptionMenuPtr->option[MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
    sOptionMenuPtr->option[MENUITEM_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
    sOptionMenuPtr->option[MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
    sOptionMenuPtr->option[MENUITEM_SOUND] = gSaveBlock2Ptr->optionsSound;
    sOptionMenuPtr->option[MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
    sOptionMenuPtr->option[MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;
    
    for (i = 0; i < MENUITEM_COUNT - 1; i++)
    {
        if (sOptionMenuPtr->option[i] > (sOptionMenuItemCounts[i]) - 1)
            sOptionMenuPtr->option[i] = 0;
    }
    SetHelpContext(HELPCONTEXT_OPTIONS);
    SetMainCallback2(CB2_OptionMenu);
}

static void OptionMenu_InitCallbacks(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void OptionMenu_SetVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB_OptionMenu);
}

static void CB2_OptionMenu(void)
{
    u8 i, state;
    state = sOptionMenuPtr->state;
    switch (state)
    {
    case 0:
        OptionMenu_InitCallbacks();
        break;
    case 1:
        InitOptionMenuBg();
        break;
    case 2:
        OptionMenu_ResetSpriteData();
        break;
    case 3:
        if (LoadOptionMenuPalette() != TRUE)
            return;
        break;
    case 4:
        PrintOptionMenuHeader();
        break;
    case 5:
        DrawOptionMenuBg();
        break;
    case 6:
        LoadOptionMenuItemNames();
        break;
    case 7:
		if (sCurrPage == 1)
		{
			for (i = 0; i < MENUITEM_COUNT_2; i++)
			{
				BufferOptionMenuString2(i);
			}
		}
		else
		{
			for (i = 0; i < MENUITEM_COUNT; i++)
			{
				BufferOptionMenuString(i);
			}
		}
    case 8:
        UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
        break;
    case 9:
        OptionMenu_PickSwitchCancel();
        break;
    default:
        SetOptionMenuTask();
		break;
    }
    sOptionMenuPtr->state++;
}

static void SetOptionMenuTask(void)
{
    CreateTask(Task_OptionMenu, 0);
    SetMainCallback2(CB2_InitOptionMenu);
}

static void InitOptionMenuBg(void)
{
    void *dest = (void *)VRAM;
    DmaClearLarge16(3, dest, VRAM_SIZE, 0x1000);    
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);    
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sOptionMenuBgTemplates, NELEMS(sOptionMenuBgTemplates));
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    InitWindows(sOptionMenuWinTemplates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_EFFECT_LIGHTEN);
    SetGpuReg(REG_OFFSET_BLDY, BLDCNT_TGT1_BG1);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_CLR);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
};

static void OptionMenu_PickSwitchCancel(void)
{
    s32 x;
    x = 0xE4 - GetStringWidth(FONT_SMALL, gText_PickSwitchCancel, 0);
    FillWindowPixelBuffer(2, PIXEL_FILL(15)); 
    AddTextPrinterParameterized3(2, FONT_SMALL, x, 0, sOptionMenuPickSwitchCancelTextColor, 0, gText_PickSwitchCancel);
    PutWindowTilemap(2);
    CopyWindowToVram(2, COPYWIN_FULL);
}

static void OptionMenu_ResetSpriteData(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static bool8 LoadOptionMenuPalette(void)
{
    switch (sOptionMenuPtr->loadPaletteState)
    {
    case 0:
        LoadBgTiles(1, GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
        break;
    case 1:
        LoadPalette(GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, BG_PLTT_ID(2), PLTT_SIZE_4BPP);
        break;
    case 2:
        LoadPalette(sOptionMenuPalette, BG_PLTT_ID(1), sizeof(sOptionMenuPalette));
        LoadPalette(GetTextWindowPalette(2), BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case 3:
        LoadStdWindowGfxOnBg(1, 0x1B3, BG_PLTT_ID(3));
        break;
    default:
        return TRUE;
    }
    sOptionMenuPtr->loadPaletteState++;
    return FALSE;
}

static void Task_OptionMenu(u8 taskId)
{
    switch (sOptionMenuPtr->loadState)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        OptionMenu_SetVBlankCallback();
        sOptionMenuPtr->loadState++;
        break;
    case 1:
        if (gPaletteFade.active)
            return;
		ReadAllCurrentSettings(taskId);
        sOptionMenuPtr->loadState++;
        break;
    case 2:
        if (((bool32)IsActiveOverworldLinkBusy()) == TRUE)
            break;
        switch (OptionMenu_ProcessInput(taskId))
        {
        case 0:
            break;
        case 1:
            sOptionMenuPtr->loadState++;
            break;
        case 2:
            LoadBgTiles(1, GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
            LoadPalette(GetUserWindowGraphics(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, BG_PLTT_ID(2), PLTT_SIZE_4BPP);
			if (sCurrPage == 1)
				BufferOptionMenuString2(sOptionMenuPtr->cursorPos);
			else
				BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
        case 3:
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        case 4:
            if (sCurrPage == 1)
				BufferOptionMenuString2(sOptionMenuPtr->cursorPos);
			else
				BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
		case 5:
			FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
			ClearStdWindowAndFrame(WIN_OPTIONS, FALSE);
			if (sCurrPage == 1)
				sCurrPage--;
			else
				sCurrPage++;
			gTasks[taskId].func = Task_ChangePage;
			break;
        }
        break;
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        sOptionMenuPtr->loadState++;
        break;
    case 4:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 5:
        CloseAndSaveOptionMenu(taskId);
        break;
    }
}

static void Task_ChangePage(u8 taskId)
{
	u8 i;
	
	HandlePageSettings(taskId);
	
    PrintOptionMenuHeader();
    PutWindowTilemap(1);
	LoadOptionMenuItemNames();
    if (sCurrPage == 1)
	{
		for (i = 0; i < MENUITEM_COUNT_2; i++)
		{
			BufferOptionMenuString2(i);
		}
	}
	else
	{
		for (i = 0; i < MENUITEM_COUNT; i++)
		{
			BufferOptionMenuString(i);
		}
	}
	sOptionMenuPtr->cursorPos = 0;
	UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
	gTasks[taskId].func = Task_OptionMenu;
}

static u8 OptionMenu_ProcessInput(u8 taskId)
{ 
    u16 current;
    u16 *curr;
	u8 dst[3];
	memcpy(dst, sOptionMenuTextColor, 3);
    if (JOY_REPT(DPAD_RIGHT))
    {
        current = sOptionMenuPtr->option[(sOptionMenuPtr->cursorPos)];
		if (sCurrPage == 1)
		{
			if (current == (sOptionMenuItemCounts2[sOptionMenuPtr->cursorPos] - 1))
				sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = 0;
			else
				sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = current + 1;
		}
		else
		{
			if (current == (sOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
				sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = 0;
			else
				sOptionMenuPtr->option[sOptionMenuPtr->cursorPos] = current + 1;
		}
        if (sOptionMenuPtr->cursorPos == MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
	else if (JOY_NEW(A_BUTTON))
    {
		if (sCurrPage == 1)
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_BACK)
			{
				return 5;
			}
		}
		else
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_NEXT)
			{
				return 5;
			}
		}
	}
    else if (JOY_REPT(DPAD_LEFT))
    {
        curr = &sOptionMenuPtr->option[sOptionMenuPtr->cursorPos];
		if (sCurrPage == 1)
		{
			if (*curr == 0)
				*curr = sOptionMenuItemCounts2[sOptionMenuPtr->cursorPos] - 1;
			else
				--*curr;
		}
		else
		{
			if (*curr == 0)
				*curr = sOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
			else
				--*curr;
		}
        
        if (sOptionMenuPtr->cursorPos == MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
    else if (JOY_REPT(DPAD_UP))
    {
		if (sCurrPage == 1)
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_QUICKNURSE)
				sOptionMenuPtr->cursorPos = MENUITEM_BACK;
			else
				sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
		}
		else
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_TEXTSPEED)
				sOptionMenuPtr->cursorPos = MENUITEM_NEXT;
			else
				sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
		}
        return 3;        
    }
    else if (JOY_REPT(DPAD_DOWN))
    {
		if (sCurrPage == 1)
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_BACK)
				sOptionMenuPtr->cursorPos = MENUITEM_QUICKNURSE;
			else
				sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
		}
		else
		{
			if (sOptionMenuPtr->cursorPos == MENUITEM_NEXT)
				sOptionMenuPtr->cursorPos = MENUITEM_TEXTSPEED;
			else
				sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
		}
        return 3;
    }
    else if (JOY_NEW(B_BUTTON))
    {
		if (sCurrPage == 1)
			return 5;
		else
			return 1;
    }
    else
    {
        return 0;
    }
}

static void BufferOptionMenuString(u8 selection)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y;
    
    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT) - 1) * selection) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT));

    switch (selection)
    {
    case MENUITEM_TEXTSPEED:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sTextSpeedOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BATTLESCENE:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sBattleSceneOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BATTLESTYLE:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sBattleStyleOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_SOUND:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sSoundOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_BUTTONMODE:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sButtonTypeOptions[sOptionMenuPtr->option[selection]]);
        break;
    case MENUITEM_FRAMETYPE:
        StringCopy(str, gText_FrameType);
        ConvertIntToDecimalStringN(buf, sOptionMenuPtr->option[selection] + 1, 1, 2);
        StringAppendN(str, buf, 3);
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, str);
        break;
    default:
        break;
    }
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static void BufferOptionMenuString2(u8 selection)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y;
    
    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT) - 1) * selection) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT));

    switch (selection)
    {
	case MENUITEM_QUICKNURSE:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sQuickNurseOptions[sOptionMenuPtr->option[selection]]);
        break;
	case MENUITEM_PERMARUN:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sPermaRunOptions[sOptionMenuPtr->option[selection]]);
        break;
	case MENUITEM_QUICKCONTINUE:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sContinueNames[sOptionMenuPtr->option[selection]]);
        break;
	case MENUITEM_EXPALL:
        AddTextPrinterParameterized3(1, FONT_NORMAL, x, y, dst, -1, sPermaRunOptions[sOptionMenuPtr->option[selection]]);
        break;
    default:
        break;
    }
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static void CloseAndSaveOptionMenu(u8 taskId)
{
    gFieldCallback = FieldCB_DefaultWarpExit;
    SetMainCallback2(gMain.savedCallback);
    FreeAllWindowBuffers();
    gSaveBlock2Ptr->optionsTextSpeed = sOptionMenuPtr->option[MENUITEM_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleSceneOff = sOptionMenuPtr->option[MENUITEM_BATTLESCENE];
    gSaveBlock2Ptr->optionsBattleStyle = sOptionMenuPtr->option[MENUITEM_BATTLESTYLE];
    gSaveBlock2Ptr->optionsSound = sOptionMenuPtr->option[MENUITEM_SOUND];
    gSaveBlock2Ptr->optionsButtonMode = sOptionMenuPtr->option[MENUITEM_BUTTONMODE];
    gSaveBlock2Ptr->optionsWindowFrameType = sOptionMenuPtr->option[MENUITEM_FRAMETYPE];
	gSaveBlock2Ptr->quickNurse = gTasks[taskId].tQuickNurse;
	gSaveBlock2Ptr->permaRun = gTasks[taskId].tPermaRun;
	gSaveBlock2Ptr->quickContinue = gTasks[taskId].tQuickContinue;
	gSaveBlock2Ptr->expAll = gTasks[taskId].tExpAll;
    SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
    FREE_AND_SET_NULL(sOptionMenuPtr);
    DestroyTask(taskId);
}

static void PrintOptionMenuHeader(void)
{
	u32 i, widthOptions, xMid;
    u8 pageDots[9] = _("");  // Array size should be at least (2 * PAGE_COUNT) -1
    widthOptions = GetStringWidth(FONT_NORMAL, gText_Option, 0);
	
	for (i = 0; i < PAGE_COUNT; i++)
    {
        if (i == sCurrPage)
            StringAppend(pageDots, gText_LargeDot);
        else
            StringAppend(pageDots, gText_SmallDot);
        if (i < PAGE_COUNT - 1)
            StringAppend(pageDots, gText_Space);            
    }
	xMid = (8 + widthOptions + 5);
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_TEXT_OPTION, FONT_NORMAL, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
	AddTextPrinterParameterized(0, FONT_NORMAL, pageDots, xMid, 1, TEXT_SKIP_DRAW, NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void DrawOptionMenuBg(void)
{
    u8 h;
    h = 2;
    
    FillBgTilemapBufferRect(1, 0x1B3, 1, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B4, 2, 2, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B5, 0x1C, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B6, 1, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B8, 0x1C, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B9, 1, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BA, 2, 5, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BB, 0x1C, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1AA, 1, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AB, 2, 6, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1AC, 0x1C, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AD, 1, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1AF, 0x1C, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1B0, 1, 0x13, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1B1, 2, 0x13, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1B2, 0x1C, 0x13, 1, 1, h);
    CopyBgTilemapBufferToVram(1);
}

static void LoadOptionMenuItemNames(void)
{
    u8 i, items;
    const u8* const* menu = NULL;

    switch (sCurrPage){
    case 0:
        items = MENUITEM_COUNT;
        menu = sOptionMenuItemsNames;
        break;
    case 1:
        items = MENUITEM_COUNT_2;
        menu = sOptionMenuItemsNames_Pg2;
        break;    
    }

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < items; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, menu[i], 8, (u8)((i * (GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SKIP_DRAW, NULL);    
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void UpdateSettingSelectionDisplay(u16 selection)
{
    u16 maxLetterHeight, y;
    
    maxLetterHeight = GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT);
    y = selection * (maxLetterHeight - 1) + 0x3A;
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(y, y + maxLetterHeight));
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0x10, 0xE0));
}
