//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  initSysUtil();

  touch_file("/mnt/usb0/.probe");
  if (!file_exists("/mnt/usb0/.probe")) {
    touch_file("/mnt/usb1/.probe");
    if (!file_exists("/mnt/usb1/.probe")) {
      printf_notification("Restoring from internal");
      if (file_exists("/system_data/priv/mms/app.bak")) {
        copy_file("/system_data/priv/mms/app.bak", "/system_data/priv/mms/app.db");
      }
      if (file_exists("/system_data/priv/mms/addcont.bak")) {
        copy_file("/system_data/priv/mms/addcont.bak", "/system_data/priv/mms/addcont.db");
      }
      if (file_exists("/user/system/webkit/secure/appcache/ApplicationCache.bak")) {
        copy_file("/user/system/webkit/secure/appcache/ApplicationCache.bak", "/user/system/webkit/secure/appcache/ApplicationCache.db");
      }
      if (file_exists("/user/system/webkit/webbrowser/appcache/ApplicationCache.bak")) {
        copy_file("/user/system/webkit/webbrowser/appcache/ApplicationCache.bak", "/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
      }      
      if (file_exists("/system_data/priv/mms/av_content_bg.bak")) {
        copy_file("/system_data/priv/mms/av_content_bg.bak", "/system_data/priv/mms/av_content_bg.db");
      }
    } else {
      printf_notification("Restoring from USB1");
      unlink("/mnt/usb1/.probe");
      mkdir("/mnt/usb1/PS4/", 0777);
      mkdir("/mnt/usb1/PS4/Backup/", 0777);
      if (file_exists("/mnt/usb1/PS4/Backup/app.db")) {
        copy_file("/mnt/usb1/PS4/Backup/app.db", "/system_data/priv/mms/app.db");
      }
      if (file_exists("/mnt/usb1/PS4/Backup/addcont.db")) {
        copy_file("/mnt/usb1/PS4/Backup/addcont.db", "/system_data/priv/mms/addcont.db");
      }
      if (file_exists("/mnt/usb1/PS4/Backup/ApplicationCache.dbsec")) {
        copy_file("/mnt/usb1/PS4/Backup/ApplicationCache.dbsec", "/user/system/webkit/secure/appcache/ApplicationCache.db");
      }
      if (file_exists("/mnt/usb1/PS4/Backup/ApplicationCache.db")) {
        copy_file("/mnt/usb1/PS4/Backup/ApplicationCache.db", "/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
      }      
      if (file_exists("/mnt/usb1/PS4/Backup/av_content_bg.db")) {
        copy_file("/mnt/usb1/PS4/Backup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");
      }
    }
  } else {
    printf_notification("Restoring from USB0");
    unlink("/mnt/usb0/.probe");
    mkdir("/mnt/usb0/PS4/", 0777);
    mkdir("/mnt/usb0/PS4/Backup/", 0777);
    if (file_exists("/mnt/usb0/PS4/Backup/app.db")) {
      copy_file("/mnt/usb0/PS4/Backup/app.db", "/system_data/priv/mms/app.db");
    }
    if (file_exists("/mnt/usb0/PS4/Backup/addcont.db")) {
      copy_file("/mnt/usb0/PS4/Backup/addcont.db", "/system_data/priv/mms/addcont.db");
    }
    if (file_exists("/mnt/usb0/PS4/Backup/ApplicationCache.dbsec")) {
        copy_file("/mnt/usb0/PS4/Backup/ApplicationCache.dbsec", "/user/system/webkit/secure/appcache/ApplicationCache.db");
    }
    if (file_exists("/mnt/usb0/PS4/Backup/ApplicationCache.db")) {
        copy_file("/mnt/usb0/PS4/Backup/ApplicationCache.db", "/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
    }     
    if (file_exists("/mnt/usb0/PS4/Backup/av_content_bg.db")) {
      copy_file("/mnt/usb0/PS4/Backup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");
    }
  }

  printf_notification("Restore complete!\nRebooting console...");

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  sceKernelSleep(10);
  reboot();

  return 0;
}
