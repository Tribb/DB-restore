#include "kernel_utils.h"

int _main(struct thread *td) {
  initKernel();
  initLibc();
  initPthread();

  uint64_t fw_version = get_fw_version();
  jailbreak(fw_version);

  initSysUtil();

  int usbdir = open("/mnt/usb0/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (usbdir == -1) {
    usbdir = open("/mnt/usb1/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (usbdir == -1) {
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
      close(usbdir);
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
    close(usbdir);
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
