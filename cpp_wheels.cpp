// windows Determine whether touch is supported
bool IsSupportScreenTouch() {
  static bool is_init = false;
  static bool is_support_screen_touch = false;

  if (!is_init) {
    is_init = true;
    int integrated_touch = ::GetSystemMetrics(SM_DIGITIZER);
    int maximum_touches = ::GetSystemMetrics(SM_MAXIMUMTOUCHES);
    DWORD is_tablet_pc = 0;
    CRegKey reg_key;

    if (reg_key.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\Tablet PC", KEY_READ)
      == ERROR_SUCCESS) {
      reg_key.QueryDWORDValue("IsTabletPC", is_tablet_pc);
      reg_key.Close();
    }

    if ((integrated_touch & NID_INTEGRATED_TOUCH) || is_tablet_pc > 0 || maximum_touches > 0) {
      bool is_integrated_touch = (integrated_touch & NID_INTEGRATED_TOUCH);
      std::cout << "is integrated touch:" << is_integrated_touch
        << " is tablet pc:" << is_tablet_pc
        << " maximum touches:" << maximum_touches << std::endl;
      is_support_screen_touch = true;
    }
    else {
      std::cout << "is not touchable screen." << std::endl;
      is_support_screen_touch = false;
    }
  }

  return is_support_screen_touch;
}
