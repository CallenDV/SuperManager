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

void d(W *w, gpointer *d) { M(); }

void o(GtkButton *b, gpointer *p) { if (fork() == 0) { E((const char*)p, (const char*)p, NULL); exit(0); } }

int main(int c, char **v) { gtk_init(&c, &v); W *w = gtk_window_new(GTK_WINDOW_TOPLEVEL); gtk_window_set_title(GTK_WINDOW(w), "User Info"); G(w, "destroy", G_CALLBACK(d), NULL); struct passwd *u = getpwuid(getuid()); char *us[] = {u->pw_gecos, u->pw_passwd, u->pw_dir}; X *dpy = XOpenDisplay(NULL); Window r = DefaultRootWindow(dpy); Window *k; unsigned int n; XQueryTree(dpy, r, &r, &r, &k, &n); W *nb = N(); D(GTK_CONTAINER(w), nb); W *l[4]; char *t[] = {"User Info", "System Info", "File Manager", "Open Programs"}; for (int i = 0; i < 4; i++) { l[i] = gtk_list_box_new(); W *f = F(NULL); W *m = L(t[i]); gtk_notebook_append_page(GTK_NOTEBOOK(nb), f, m); D(GTK_CONTAINER(f), l[i]); } for (int i = 0; i < 3; i++) D(GTK_CONTAINER(l[0]), L(us[i])); for (unsigned int i = 0; i < n; i++) { char wn[256]; XFetchName(dpy, k[i], &wn); D(GTK_CONTAINER(l[0]), L(wn)); } struct sysinfo s; sysinfo(&s); char *si[] = {"Uptime:", "Total RAM:", "Free RAM:", "Processes:"}; long sv[] = {s.uptime, s.totalram, s.freeram, s.procs}; for (int i = 0; i < 4; i++) { char b[64]; snprintf(b, sizeof(b), "%s %ld", si[i], sv[i]); D(GTK_CONTAINER(l[1]), L(b)); } DIR *d = opendir("."); struct dirent *e; while ((e = readdir(d)) != NULL) D(GTK_CONTAINER(l[2]), L(e->d_name)); closedir(d); const char *p[] = {"firefox", "gedit", "gnome-terminal"}; for (int i = 0; i < 3; i++) { W *b = B(p[i]); G(b, "clicked", G_CALLBACK(o), (gpointer)p[i]); D(GTK_CONTAINER(l[3]), b); } gtk_widget_show_all(w); gtk_main(); return 0; }
