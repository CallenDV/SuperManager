#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define PRINT printf
#define USER_INFO u->pw_gecos
#define HOME_DIR u->pw_dir
#define SYSTEM_INFO struct SystemInfo

SYSTEM_INFO { long uptime, total_ram, free_ram; int processes; float cpu_usage; };

void printUserInfo(struct passwd *u) {
    PRINT("**User Info:**\n   - **Full Name:** %s\n   - **Home Directory:** %s\n\n", USER_INFO, HOME_DIR);
}

void listOpenWindows() {
    PRINT("**Window List:**\n"); 

    FILE *fp = popen("wmctrl -l", "r");
    if (fp != NULL) {
        char windowInfo[256];
        while (fgets(windowInfo, sizeof(windowInfo), fp) != NULL) {
            PRINT("   - %s", windowInfo);
        }
        pclose(fp);
    }
}

void printSystemInfo(SYSTEM_INFO *s) {
    PRINT("**System Info:**\n   - **Uptime:** %ld seconds\n   - **Total RAM:** %ld KB\n   - **Free RAM:** %ld KB\n   - **Processes:** %d\n   - **CPU Usage:** %.2f%%\n\n",
          s->uptime, s->total_ram, s->free_ram, s->processes, s->cpu_usage);
}

void listFilesAndFolders() {
    PRINT("**File Manager:**\n"); 

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(HOME_DIR)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            PRINT("   - %s\n", ent->d_name);
        }
        closedir(dir);
    }
}

void launchProgram(const char *program) {
    PRINT("   - Launch %s\n", program); 

    char command[256];
    snprintf(command, sizeof(command), "gnome-terminal -e %s", program);
    system(command);
}

void printHelp() {
    PRINT("**Help:**\n   - Instructions on how to use each feature.\n   - Detailed explanations for each tab.\n");
}

int main() {
    struct passwd *u = getpwuid(getuid());
    SYSTEM_INFO s;
    s.uptime = s.total_ram = s.free_ram = s.processes = 0;

    PRINT("Enhanced User Info\n\n");
    printUserInfo(u);
    listOpenWindows();
    printSystemInfo(&s);
    listFilesAndFolders();

    const char *programs[] = {"firefox", "gedit", "gnome-terminal"};
    PRINT("**Open Programs:**\n");
    for (int i = 0; i < 3; i++) {
        launchProgram(programs[i]);
    }
    
    printHelp();
    
    return 0;
}