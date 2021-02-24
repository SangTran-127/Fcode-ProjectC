#include <gtk/gtk.h>
static void load_css(void)
{
	GtkCssProvider * provider;
	GdkDisplay * display;
	GdkScreen * screen;
	const gchar *css_style_file = "style.css";
	GFile *css_fp = g_file_new_for_path(css_style_file);
	GError *error = 0;
	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_file(provider, css_fp, &error);
	g_object_unref(provider);
}
static void activate(GtkApplication *app, gpointer data)
{
    load_css();
    GtkWidget *window;
    GtkWidget *addressChangeInforLabel, *nameChangeInforLabel, *phoneChangeInforLabel;

    GtkWidget *addressChangeInforEntry, *nameChangeInforEntry, *phoneChangeInforEntry;

    GtkWidget *updateChangeInforButton, *backChangeInforButton;
    GtkWidget *askBackChangeInforLabel;
    GtkWidget *gridChangeInfor, *containerChangeInfor, *hboxFooter;
    GtkWidget *changeInforImg;
    //set up
    containerChangeInfor = gtk_hbox_new(1, 0);
    gridChangeInfor = gtk_grid_new();
    //
    changeInforImg = gtk_image_new_from_file("change_infor.png");
    addressChangeInforEntry = gtk_entry_new();
    nameChangeInforEntry = gtk_entry_new();
    phoneChangeInforEntry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(addressChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "emblem-mail");
    gtk_entry_set_placeholder_text(addressChangeInforEntry, "Enter your address");
    gtk_entry_set_icon_from_icon_name(nameChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "contact-new");
    gtk_entry_set_placeholder_text(nameChangeInforEntry, "Enter your full name");
    gtk_entry_set_icon_from_icon_name(phoneChangeInforEntry, GTK_ENTRY_ICON_PRIMARY, "phone");
    gtk_entry_set_placeholder_text(phoneChangeInforEntry, "Enter your phone number");
    //
    askBackChangeInforLabel = gtk_label_new("Change your mind ?");
    backChangeInforButton = gtk_button_new_with_label("Back");
    gtk_widget_set_name(backChangeInforButton, "backChangeInforButton");

    hboxFooter = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxFooter, askBackChangeInforLabel, 0, 0, 10);
    gtk_box_pack_end(hboxFooter, backChangeInforButton, 0, 0, 0);

    addressChangeInforLabel = gtk_label_new("Address: ");
    nameChangeInforLabel = gtk_label_new("Full name: ");
    phoneChangeInforLabel = gtk_label_new("Phone number: ");
    updateChangeInforButton = gtk_button_new_with_label("Update");

    //
    gtk_grid_attach(gridChangeInfor, nameChangeInforLabel, 0, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, nameChangeInforEntry, 1, 0, 1, 1);
    gtk_grid_attach(gridChangeInfor, phoneChangeInforLabel, 0, 1, 1, 1);
    gtk_grid_attach(gridChangeInfor, phoneChangeInforEntry, 1, 1, 1, 1);
    gtk_grid_attach(gridChangeInfor, addressChangeInforLabel, 0, 2, 1, 1);
    gtk_grid_attach(gridChangeInfor, addressChangeInforEntry, 1, 2, 1, 1);
    gtk_grid_attach(gridChangeInfor, updateChangeInforButton, 1, 3, 1, 1);
    gtk_grid_attach(gridChangeInfor, hboxFooter, 1, 4, 1, 1);
    gtk_grid_set_column_spacing(gridChangeInfor, 10);
    gtk_grid_set_row_spacing(gridChangeInfor, 10);
    gtk_widget_set_name(gridChangeInfor, "gridChangeInfor");
    gtk_box_pack_start(containerChangeInfor, gridChangeInfor, 0, 0, 0);
    gtk_box_pack_end(containerChangeInfor, changeInforImg, 0, 0, 0);
    gtk_widget_set_name(updateChangeInforButton, "changeInforButton");
    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Change Information");
	gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, containerChangeInfor);
	gtk_widget_show_all(window);
}
int main(int argc, char **argv)
{
    GtkAllocation * app;
	int status;
	app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
