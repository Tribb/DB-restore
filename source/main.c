#include "ps4.h"

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

  jailbreak();

  initSysUtil();

  FILE *usbdir = fopen("/mnt/usb0/.dirtest", "w");
  if (!usbdir) {
    usbdir = fopen("/mnt/usb1/.dirtest", "w");
    if (!usbdir) {
      printf_notification("Restoring from internal");
      if (file_exists("/system_data/priv/mms/app.bak")) {
        copy_file("/system_data/priv/mms/app.bak", "/system_data/priv/mms/app.db");
      }
      if (file_exists("/system_data/priv/mms/addcont.bak")) {
        copy_file("/system_data/priv/mms/addcont.bak", "/system_data/priv/mms/addcont.db");
      }
      if (file_exists("/system_data/priv/mms/av_content_bg.bak")) {
        copy_file("/system_data/priv/mms/av_content_bg.bak", "/system_data/priv/mms/av_content_bg.db");
      }
    } else {
      fclose(usbdir);
      printf_notification("Restoring from USB1");
      unlink("/mnt/usb1/.dirtest");
      mkdir("/mnt/usb1/DB_Backup/", 0777);
      if (file_exists("/mnt/usb1/DB_Backup/app.db")) {
        copy_file("/mnt/usb1/DB_Backup/app.db", "/system_data/priv/mms/app.db");
      }
      if (file_exists("/mnt/usb1/DB_Backup/addcont.db")) {
        copy_file("/mnt/usb1/DB_Backup/addcont.db", "/system_data/priv/mms/addcont.db");
      }
      if (file_exists("/mnt/usb1/DB_Backup/av_content_bg.db")) {
        copy_file("/mnt/usb1/DB_Backup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");
      }
    }
  } else {
    fclose(usbdir);
    printf_notification("Restoring from USB0");
    unlink("/mnt/usb0/.dirtest");
    mkdir("/mnt/usb0/DB_Backup/", 0777);
    if (file_exists("/mnt/usb0/DB_Backup/app.db")) {
      copy_file("/mnt/usb0/DB_Backup/app.db", "/system_data/priv/mms/app.db");
    }
    if (file_exists("/mnt/usb0/DB_Backup/addcont.db")) {
      copy_file("/mnt/usb0/DB_Backup/addcont.db", "/system_data/priv/mms/addcont.db");
    }
    if (file_exists("/mnt/usb0/DB_Backup/av_content_bg.db")) {
      copy_file("/mnt/usb0/DB_Backup/av_content_bg.db", "/system_data/priv/mms/av_content_bg.db");
    }
  }

  printf_notification("Restore complete!\nRebooting console...");
  sceKernelSleep(8);
  reboot();

  return 0;
}
