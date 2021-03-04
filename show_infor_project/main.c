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
    GtkWidget *containerShowInfor, *headerTiku, *mainSectionInfor, *mainInfor;
    GtkWidget *pictureInfor, *backShowInforButton;
    GtkWidget *headerLabel, *nameInforLabel, *addressLabel, *dobLabel;
    GtkWidget *headerLabelShow, *nameInforLabelShow, *addressLabelShow, *dobLabelShow;
    GtkWidget *welcomeChangeInforLabel, *nameShopLabel;
    load_css();
    backShowInforButton = gtk_button_new_with_label("Back");
    gtk_widget_set_name(backShowInforButton, "backShowInforButton");
    welcomeChangeInforLabel = gtk_label_new("Welcome back!");
    nameShopLabel = gtk_label_new("Tiku");
    headerTiku = gtk_hbox_new(0, 0);
    gtk_box_pack_start(headerTiku, welcomeChangeInforLabel, 0, 0, 0);
    gtk_box_pack_end(headerTiku, nameShopLabel, 0, 0, 0);
    gtk_widget_set_name(headerTiku, "headerTiku");

    pictureInfor = gtk_image_new_from_file("person.png");
    nameInforLabel = gtk_label_new("Your full name: ");
    addressLabel = gtk_label_new("Your address: ");
    dobLabel = gtk_label_new("Your date of birth: ");
    gtk_widget_set_name(pictureInfor, "pictureInfor");
    nameInforLabelShow = gtk_label_new("William Henry Gates III");
    addressLabelShow = gtk_label_new("500 5th Ave N, Seattle, WA 98109, United States");
    dobLabelShow = gtk_label_new("28/08/1955");
    mainSectionInfor = gtk_vbox_new(0, 0);
    gtk_box_pack_start(mainSectionInfor, nameInforLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, nameInforLabelShow,0, 0, 0);
    gtk_box_pack_start(mainSectionInfor, addressLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, addressLabelShow,0, 0, 0);
    gtk_box_pack_start(mainSectionInfor, dobLabel,0, 0, 10);
    gtk_box_pack_start(mainSectionInfor, dobLabelShow,0, 0, 0);
    gtk_box_pack_end(mainSectionInfor, backShowInforButton, 0, 0, 10);
    gtk_widget_set_name(mainSectionInfor, "mainSectionInfor");
    gtk_widget_set_name(welcomeChangeInforLabel, "welcomeChangeInforLabel");
    gtk_widget_set_name(nameShopLabel, "nameShopLabel");
    gtk_widget_set_name(nameInforLabel, "nameInforLabel");
    gtk_widget_set_name(addressLabel, "addressLabel");
    gtk_widget_set_name(dobLabel, "dobLabel");
    mainInfor = gtk_hbox_new(0, 0);
    gtk_box_pack_start(mainInfor, pictureInfor, 0, 0, 0);
    gtk_box_pack_end(mainInfor, mainSectionInfor, 0, 0, 0);

    containerShowInfor = gtk_vbox_new(0, 0);
    gtk_box_pack_start(containerShowInfor, headerTiku, 0, 0, 0);
    gtk_box_pack_start(containerShowInfor , mainInfor, 0, 0, 0);
    gtk_widget_set_name(containerShowInfor, "containerShowInfor");
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Show Information");
    gtk_window_set_default_size(GTK_WINDOW(window),500,200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(window, containerShowInfor);
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
