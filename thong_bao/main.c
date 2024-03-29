#include <gtk/gtk.h>
static void load_css(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path(css_style_file);
    GError *error               = 0;
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);
    g_object_unref(provider);
}
static void activate(GtkApplication *app, gpointer data) {
    GtkWidget *window;
    load_css();
    GtkWidget *alert;
    GtkWidget *alertButton;
    GtkWidget *vboxAlert;
    GtkWidget *hboxAlert;
    GtkWidget *nonLabelAlert;
    nonLabelAlert = gtk_label_new("             ");
    vboxAlert = gtk_vbox_new(1, 0);
    alertButton = gtk_button_new_with_label("close");
    alert = gtk_label_new("Hello!!!");
    hboxAlert = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxAlert, nonLabelAlert, 0, 0, 0);
    gtk_box_pack_end(hboxAlert, alertButton, 0, 0, 0);
    gtk_box_pack_start(vboxAlert, alert, 0, 0, 10);
    gtk_box_pack_start(vboxAlert, hboxAlert, 0, 0, 0);
    gtk_widget_set_name(alertButton, "alertButton");
    gtk_widget_set_name(vboxAlert, "vboxAlert");
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "alert");
    gtk_window_set_default_size(GTK_WINDOW(window),200,20);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(window, vboxAlert);
    gtk_widget_show_all (window);
}
int main(int argc, char **argv) {
    GtkAllocation *app;
    int status;
    app = gtk_application_new("app.hello",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
