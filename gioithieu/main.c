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
    GtkWidget *vboxIntro;
    GtkWidget *hboxSection;
    GtkWidget *vBoxContainer;
    GtkWidget *navbar;
    GtkWidget *logo;
    GtkWidget *header; //hbox
    GtkWidget *main;
    GtkWidget *picture;
    GtkWidget *contactButton, *aboutButton, *homeButton, *loginButton, *signUpButton;
    GtkWidget *goShoppingNow; //button
    GtkWidget *tikuLabel;
    GtkWidget *shoppingLabel;
    GtkWidget *slogan;
    tikuLabel = gtk_label_new("Tiku");
    gtk_widget_set_name(tikuLabel, "tiku");
    shoppingLabel = gtk_label_new("Shopping online");
    gtk_widget_set_name(shoppingLabel, "shoppingLabel");
    slogan = gtk_label_new("A few clicks is all it takes.\n\Life is hard enough already. Let us make it a little easier.\n\The quality service you expect.");
    contactButton = gtk_button_new_with_label("Contact");
    gtk_widget_set_name(contactButton, "contact");
    aboutButton = gtk_button_new_with_label("About");
    gtk_widget_set_name(aboutButton, "about");
    homeButton = gtk_button_new_with_label("Home");
    gtk_widget_set_name(homeButton, "home");
    signUpButton = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(signUpButton, "signup");
    loginButton = gtk_button_new_with_label("Login");
    gtk_widget_set_name(loginButton, "loginButton");
    goShoppingNow = gtk_button_new_with_label("Go Shopping Now --->");
    gtk_widget_set_name(goShoppingNow, "goShopping");
    logo = gtk_label_new("Tiku");

    gtk_widget_set_name(logo, "logo");

    navbar = gtk_hbox_new(0, 0);

    gtk_box_pack_start(navbar, homeButton, 0, 0, 0);
    gtk_box_pack_start(navbar, aboutButton, 0, 0, 0);
    gtk_box_pack_start(navbar, contactButton, 0, 0, 0);
    gtk_box_pack_start(navbar, signUpButton, 0, 0, 0);
    gtk_box_pack_start(navbar, loginButton, 0, 0, 0);

    header = gtk_hbox_new(0, 0);
    gtk_box_pack_start(header, logo, 0, 0, 0);
    gtk_box_pack_end(header, navbar, 0, 0, 0);
    gtk_widget_set_name(header, "header");

    vboxIntro = gtk_vbox_new(0, 0);
    gtk_widget_set_name(vboxIntro, "vboxIntro");
    gtk_box_pack_start(vboxIntro, tikuLabel, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, shoppingLabel, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, slogan, 0, 0, 0);
    gtk_box_pack_start(vboxIntro, goShoppingNow, 0, 0, 0);


    picture = gtk_image_new_from_file("background_landing_page.png");

    hboxSection = gtk_hbox_new(0, 0);
    gtk_box_pack_start(hboxSection, vboxIntro, 0, 0, 0);
    gtk_box_pack_start(hboxSection, picture, 0, 0, 0);

    vBoxContainer = gtk_vbox_new(0, 0);
    gtk_box_pack_start(vBoxContainer, header, 0, 0, 0);
    gtk_box_pack_start(vBoxContainer, hboxSection, 0, 0, 0);





    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Tiku");
	gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, vBoxContainer);
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
