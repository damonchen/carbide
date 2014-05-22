#include "stdafx.h"
#include "controltype.h"

static const KeyValue control_type[] = {
	{"Button", UIA_ButtonControlTypeId},
	{"Calendar", UIA_CalendarControlTypeId},
	{"CheckBox", UIA_CheckBoxControlTypeId},
	{"ComboBox", UIA_ComboBoxControlTypeId},
	{"Edit", UIA_EditControlTypeId},
	{"Hyperlink", UIA_HyperlinkControlTypeId},
	{"Image", UIA_ImageControlTypeId},
	{"ListItem", UIA_ListItemControlTypeId},
	{"List", UIA_ListControlTypeId},
	{"Menu", UIA_MenuControlTypeId},
	{"MenuBar", UIA_MenuBarControlTypeId},
	{"MenuItem", UIA_MenuItemControlTypeId},
	{"ProgressBar", UIA_ProgressBarControlTypeId},
	{"RadioButton", UIA_RadioButtonControlTypeId},
	{"ScrollBar", UIA_ScrollBarControlTypeId},
	{"Slider", UIA_SliderControlTypeId},
	{"Spinner", UIA_SpinnerControlTypeId},
	{"StatusBar", UIA_StatusBarControlTypeId},
	{"Tab", UIA_TabControlTypeId},
	{"TabItem", UIA_TabItemControlTypeId},
	{"Text", UIA_TextControlTypeId},
	{"ToolBar", UIA_ToolBarControlTypeId},
	{"ToolTip", UIA_ToolTipControlTypeId},
	{"Tree", UIA_TreeControlTypeId},
	{"TreeItem", UIA_TreeItemControlTypeId},
	{"Custom", UIA_CustomControlTypeId},
	{"Group", UIA_GroupControlTypeId},
	{"Thumb", UIA_ThumbControlTypeId},
	{"DataGrid", UIA_DataGridControlTypeId},
	{"DataItem", UIA_DataItemControlTypeId},
	{"Document", UIA_DocumentControlTypeId},
	{"SplitButton", UIA_SplitButtonControlTypeId},
	{"Window", UIA_WindowControlTypeId},
	{"Pane", UIA_PaneControlTypeId},
	{"Header", UIA_HeaderControlTypeId},
	{"HeaderItem", UIA_HeaderItemControlTypeId},
	{"Table", UIA_TableControlTypeId},
	{"TitleBar", UIA_TitleBarControlTypeId},
	{"Separator", UIA_SeparatorControlTypeId},
	{NULL, NULL},
};

CString FindControlType( CONTROLTYPEID id )
{
	static int length = sizeof(control_type) / sizeof(control_type[0]);
	for (int i=0; i<length; ++i){
		if( control_type[i].id == id ){
			return CString(control_type[i].name);
		}
	}
	return _T("");
}
