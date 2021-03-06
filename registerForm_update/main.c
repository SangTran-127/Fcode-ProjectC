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
    GtkWidget *hboxRegisterRole;
    GtkWidget *chooseBuyButton, *chooseSaleButton;
    GtkWidget *changeOption, *registerBackground;
    GtkWidget *registerLabel, *inforRegisterLabel, *askRegisterLabel, *dayLabel, *monthLabel, *yearLabel, *imgLabel;
    GtkWidget *vboxRegisterContainer, *headerBox, *userNamehBox, *dateRegisterBox, *boxAllRegister, *imgBox;
    GtkWidget *firstNameEntry, *lastNameEntry, *emailEntry, *passwordEntry, *reenterPasswordEntry;
    GtkWidget *registerButton, *backRegisterButton, *imgButton, *clearButton;
    GtkWidget *monthSpinButton, *yearSpinButton, *daySpinButton;

    chooseBuyButton = gtk_button_new_with_label("Regist as a customer");
    chooseSaleButton = gtk_button_new_with_label("Regist as a saler");
    hboxRegisterRole = gtk_hbox_new(1, 0);
    gtk_box_pack_start(hboxRegisterRole, chooseBuyButton, 1, 0, 10);
    gtk_box_pack_start(hboxRegisterRole, chooseSaleButton, 1, 0, 10);
    gtk_widget_set_name(chooseBuyButton, "chooseBuyButton");
    gtk_widget_set_name(chooseSaleButton, "chooseSaleButton");
    boxAllRegister = gtk_hbox_new(0, 10);
    firstNameEntry = gtk_entry_new();
    lastNameEntry = gtk_entry_new();
    emailEntry = gtk_entry_new();
    registerBackground = gtk_image_new_from_file("background.png");
    imgButton = gtk_button_new_from_icon_name("user-home", 0);
    imgLabel = gtk_label_new("Add your first avatar");
    dayLabel =  gtk_label_new("Date");
    monthLabel = gtk_label_new("Month");
    yearLabel = gtk_label_new("Year");
    monthSpinButton = gtk_spin_button_new_with_range(1, 12, 1);
    daySpinButton = gtk_spin_button_new_with_range(1, 31, 1);
    yearSpinButton = gtk_spin_button_new_with_range(1900, 2021, 1);
    passwordEntry = gtk_entry_new();
    reenterPasswordEntry = gtk_entry_new();
    registerLabel = gtk_label_new("------------Register------------");
    gtk_widget_set_name(registerLabel, "registerLabel");
    inforRegisterLabel = gtk_label_new("Create your account. It's free and only takes a minute");
    //registerButton = gtk_button_new_with_label("Register Now");
    //gtk_widget_set_name(registerButton, "registerButton");
    askRegisterLabel = gtk_label_new("Wanna change your option?");
    backRegisterButton = gtk_button_new_with_label("Back");
    clearButton = gtk_button_new_with_label("Clear");
    gtk_widget_set_name(clearButton, "clearButton");
    gtk_widget_set_name(backRegisterButton,"backRegisterButton");
    gtk_entry_set_placeholder_text(firstNameEntry, "First name");
    gtk_entry_set_placeholder_text(lastNameEntry, "Last name");
    gtk_entry_set_placeholder_text(emailEntry, "Email address");
    gtk_entry_set_icon_from_icon_name(emailEntry, GTK_POS_RIGHT, "mail-read");
    gtk_entry_set_placeholder_text(passwordEntry, "Password");
    gtk_entry_set_icon_from_icon_name(passwordEntry, GTK_POS_RIGHT, "dialog-password");
    gtk_entry_set_visibility(passwordEntry, FALSE);
    gtk_entry_set_placeholder_text(reenterPasswordEntry, "Confirm password");
    gtk_entry_set_icon_from_icon_name(reenterPasswordEntry, GTK_POS_RIGHT, "dialog-password");
    gtk_entry_set_visibility(reenterPasswordEntry, FALSE);
    imgBox = gtk_hbox_new(0, 20);
    gtk_box_pack_start(imgBox, imgLabel, 0, 0, 0);
    gtk_box_pack_start(imgBox, imgButton, 0, 0, 0);
    changeOption = gtk_hbox_new(0, 10);
    gtk_box_pack_start(changeOption, clearButton, 0, 0, 0);
    gtk_box_pack_end(changeOption, backRegisterButton, 0, 0, 0);
    gtk_box_pack_end(changeOption, askRegisterLabel, 0, 0, 0);
    headerBox = gtk_vbox_new(0, 15);
    gtk_box_pack_start(headerBox, registerLabel, 0, 0, 0);
    gtk_box_pack_start(headerBox, inforRegisterLabel, 0, 0, 0);
    userNamehBox = gtk_hbox_new(0, 10);
    gtk_box_pack_start(userNamehBox, firstNameEntry, 0, 0, 0);
    gtk_box_pack_start(userNamehBox, lastNameEntry, 0, 0, 0);
    dateRegisterBox = gtk_hbox_new(0, 5);
    gtk_box_pack_start(dateRegisterBox, dayLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, daySpinButton, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, monthLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, monthSpinButton, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, yearLabel, 0, 0, 0);
    gtk_box_pack_start(dateRegisterBox, yearSpinButton, 0, 0, 0);

    vboxRegisterContainer = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vboxRegisterContainer, headerBox, 0, 0, 30);
    gtk_box_pack_start(vboxRegisterContainer, userNamehBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, emailEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, dateRegisterBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, imgBox, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, passwordEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, reenterPasswordEntry, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, hboxRegisterRole, 0, 0, 10);
   // gtk_box_pack_start(vboxRegisterContainer, registerButton, 0, 0, 10);
    gtk_box_pack_start(vboxRegisterContainer, changeOption, 0, 0, 10);
    gtk_box_pack_start(boxAllRegister, registerBackground, 0, 0, 0);
    gtk_box_pack_start(boxAllRegister, vboxRegisterContainer, 0, 0, 0);
    gtk_widget_set_name(boxAllRegister,"boxAllRegister");
    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Register-Form");
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, boxAllRegister);
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
