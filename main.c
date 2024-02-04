#include <gtk/gtk.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#include <dirent.h>
#include <unistd.h>

#define G g_signal_connect
#define D gtk_container_add
#define X Display
#define W GtkWidget
#define F gtk_frame_new
#define L gtk_label_new
#define N gtk_notebook_new
#define B gtk_button_new_with_label
#define M gtk_main_quit
#define E execlp

struct SystemInfo{long u,t,f;int p;float c;};

void d(W *w, gpointer *d) { M(); }
void o(GtkButton *b, gpointer *p) { if (fork() == 0) { E((const char*)p, (const char*)p, NULL); exit(0); } }

void s(W *h, gpointer *t) {
    const char *i = "**User Info:**\nThis tab displays information about the current user.\n"
                    "   - **Full Name:** The user's full name.\n"
                    "   - **Password:** Encrypted password (not shown for security).\n"
                    "   - **Home Directory:** The user's home directory.\n\n"
                    "**System Info:**\nHere, you can find details about the system's performance.\n"
                    "   - **Uptime:** Time since the system was last started.\n"
                    "   - **Total RAM:** The total amount of RAM in the system.\n"
                    "   - **Free RAM:** The amount of free RAM available.\n"
                    "   - **Processes:** The number of running processes.\n"
                    "   - **CPU Usage:** The current CPU usage percentage.\n\n"
                    "**File Manager:**\nExplore the contents of the current directory.\n"
                    "   - Files and folders are listed here.\n\n"
                    "**Open Programs:**\nLaunch predefined programs from this tab.\n"
                    "   - Click on a button to open the associated program.\n\n"
                    "**Help:**\nThis tab provides instructions on how to use each feature.\n"
                    "   - Click on 'Show Help' to view detailed explanations.\n";

    gtk_label_set_text(GTK_LABEL(h), i);
    gtk_widget_show_all(h);
}

int main(int c, char **v) { gtk_init(&c, &v); W *w = gtk_window_new(GTK_WINDOW_TOPLEVEL); gtk_window_set_title(GTK_WINDOW(w), "Enhanced User Info"); G(w, "destroy", G_CALLBACK(d), NULL); struct passwd *u = getpwuid(getuid()); char *us[] = {u->pw_gecos, u->pw_passwd, u->pw_dir}; X *dpy = XOpenDisplay(NULL); Window r = DefaultRootWindow(dpy); Window *k; unsigned int n; XQueryTree(dpy, r, &r, &r, &k, &n); W *nb = N(); D(GTK_CONTAINER(w), nb); W *l[5]; char *t[] = {"User Info", "System Info", "File Manager", "Open Programs", "Help"}; for (int i = 0; i < 5; i++) { l[i] = gtk_list_box_new(); W *f = F(NULL); W *m = L(t[i]); gtk_notebook_append_page(GTK_NOTEBOOK(nb), f, m); D(GTK_CONTAINER(f), l[i]); } for (int i = 0; i < 3; i++) D(GTK_CONTAINER(l[0]), L(us[i])); for (unsigned int i = 0; i < n; i++) { char wn[256]; XFetchName(dpy, k[i], &wn); D(GTK_CONTAINER(l[0]), L(wn)); } struct SystemInfo s; s.u=s.t=s.f=s.p=0; getSystemInfo(&s); char *si[] = {"Uptime:", "Total RAM:", "Free RAM:", "Processes:"}; long sv[] = {s.u, s.t, s.f, s.p}; for (int i = 0; i < 4; i++) { char b[64]; snprintf(b, sizeof(b), "%s %ld", si[i], sv[i]); D(GTK_CONTAINER(l[1]), L(b)); } DIR *d = opendir("."); struct dirent *e; while ((e = readdir(d)) != NULL) D(GTK_CONTAINER(l[2]), L(e->d_name)); closedir(d); const char *p[] = {"firefox", "gedit", "gnome-terminal"}; for (int i = 0; i < 3; i++) { W *b = B(p[i]); G(b, "clicked", G_CALLBACK(o), (gpointer)p[i]); D(GTK_CONTAINER(l[3]), b); } W *h = L(""); D(GTK_CONTAINER(l[4]), h); W *hb = B("Show Help"); G(hb, "clicked", G_CALLBACK(s), (gpointer)h); D(GTK_CONTAINER(l[4]), hb); gtk_widget_show_all(w); gtk_main(); return 0;
