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
    //box
    GtkWidget *section1, *section2, *section3;
    GtkWidget *headerManage, *containerMange, *mainSectionMange, *addBox, *changeBox, *updateBox;
    GtkWidget *contentNameAdd, *contentPriceAdd, *contentIdChange, *contentNameChange, *contentPriceChange, *contentIdDelete, *contentIdUpdate, *contentPercent;
    //label
    GtkWidget *helloManageLabel, *nameAddLabel, *nameChangeLabel, *priceAddLabel, *priceChangeLabel, *idChangeLabel, *idDeleteLabel, *idUpdateLabel, *percentSaleLabel;
    //img
    GtkWidget *img1, *img2, *img3;
    //button
    GtkWidget *backManageButton, *addManageButton, *changeManageButton, *deleteManageButton, *updateManageButton;
    //entry
    GtkWidget *nameAddEntry, *nameChangeEntry, *priceAddEntry, *priceChangeEntry, *idChangeEntry, *idDeleteEntry, *idUpdateEntry, *percentSaleEntry;
    //khoi tao
    helloManageLabel = gtk_label_new("Hello saler! ");
    nameAddLabel = gtk_label_new("Name of product: ");
    nameChangeLabel = gtk_label_new("Name of product: ");
    priceAddLabel = gtk_label_new("Price: ");
    priceChangeLabel = gtk_label_new("Price: ");
    idChangeLabel = gtk_label_new("Id product: ");
    idDeleteLabel = gtk_label_new("Id product: ");
    idUpdateLabel = gtk_label_new("Id product: ");
    percentSaleLabel = gtk_label_new("%sale: ");

    backManageButton = gtk_button_new_with_label("Back");
    gtk_widget_set_name(backManageButton, "backManageButton");
    addManageButton = gtk_button_new_with_label("Add");
    gtk_widget_set_name(addManageButton, "addManageButton");
    changeManageButton = gtk_button_new_with_label("Change");
    gtk_widget_set_name(changeManageButton, "changeManageButton");
    deleteManageButton = gtk_button_new_with_label("Delete");
    gtk_widget_set_name(deleteManageButton, "deleteManageButton");
    updateManageButton = gtk_button_new_with_label("Update");
    gtk_widget_set_name(updateManageButton, "updateManageButton");

    nameAddEntry = gtk_entry_new();
    nameChangeEntry = gtk_entry_new();
    priceAddEntry = gtk_entry_new();
    priceChangeEntry = gtk_entry_new();
    idChangeEntry = gtk_entry_new();
    idDeleteEntry = gtk_entry_new();
    idUpdateEntry = gtk_entry_new();
    percentSaleEntry = gtk_entry_new();
    //
    contentNameAdd = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentNameAdd, nameAddLabel, 0, 0, 0);
    gtk_box_pack_end(contentNameAdd, nameAddEntry, 0, 0, 0);
    contentPriceAdd = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentPriceAdd, priceAddLabel, 0, 0, 0);
    //
    contentNameChange = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentNameChange, nameChangeLabel, 0, 0, 0);
    gtk_box_pack_end(contentNameChange, nameChangeEntry, 0, 0, 0);
    gtk_box_pack_end(contentPriceAdd, priceAddEntry, 0, 0, 0);
    contentIdChange = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentIdChange, idChangeLabel, 0, 0, 0);
    gtk_box_pack_end(contentIdChange, idChangeEntry, 0, 0, 0);
    contentPriceChange = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentPriceChange, priceChangeLabel, 0, 0, 0);
    gtk_box_pack_end(contentPriceChange, priceChangeEntry, 0, 0, 0);
    //
    contentIdDelete = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentIdDelete, idDeleteLabel, 0, 0, 0);
    gtk_box_pack_end(contentIdDelete, idDeleteEntry, 0, 0, 0);
    contentIdUpdate = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentIdUpdate, idUpdateLabel, 0, 0, 0);
    gtk_box_pack_end(contentIdUpdate, idUpdateEntry, 0, 0, 0);
    contentPercent = gtk_hbox_new(0, 10);
    gtk_box_pack_start(contentPercent, percentSaleLabel, 0, 0, 0);
    gtk_box_pack_end(contentPercent, percentSaleEntry, 0, 0, 0);
    //
    headerManage = gtk_hbox_new(0, 0);
    gtk_box_pack_start(headerManage, helloManageLabel, 0, 0, 0);
    gtk_box_pack_end(headerManage, backManageButton, 0, 0, 0);

    addBox = gtk_vbox_new(0, 10);
    gtk_box_pack_start(addBox, contentNameAdd, 0, 0, 0);
    gtk_box_pack_start(addBox, contentPriceAdd, 0, 0, 0);
    gtk_box_pack_start(addBox, addManageButton, 0, 0, 0);
    gtk_widget_set_name(addBox, "addBox");

    changeBox = gtk_vbox_new(0, 10);
    gtk_box_pack_start(changeBox, contentIdChange, 0, 0, 0);
    gtk_box_pack_start(changeBox, contentNameChange, 0, 0, 0);
    gtk_box_pack_start(changeBox, contentPriceChange, 0, 0, 0);
    gtk_box_pack_start(changeBox, changeManageButton, 0, 0, 0);
    gtk_widget_set_name(changeBox, "changeBox");

    updateBox = gtk_vbox_new(0, 5);
    gtk_box_pack_start(updateBox, contentIdDelete, 0, 0, 0);
    gtk_box_pack_start(updateBox, deleteManageButton, 0, 0, 0);
    gtk_box_pack_start(updateBox, contentIdUpdate, 0, 0, 0);
    gtk_box_pack_start(updateBox, contentPercent, 0, 0, 0);
    gtk_box_pack_end(updateBox, updateManageButton, 0, 0, 0);
    gtk_widget_set_name(updateBox, "updateBox");

    /*
    mainSectionMange = gtk_hbox_new(1, 0);
    gtk_box_pack_start(mainSectionMange, addBox, 0, 0, 20);
    gtk_box_pack_start(mainSectionMange, changeBox, 0, 0, 20);
    gtk_box_pack_end(mainSectionMange, updateBox, 0, 0, 20);
    */
    img1 = gtk_image_new_from_file("img1.png");
    img2 = gtk_image_new_from_file("img2.png");
    img3 = gtk_image_new_from_file("img3.png");

    section1 = gtk_hbox_new(1, 0);
    section2 = gtk_hbox_new(1, 0);
    section3 = gtk_hbox_new(1, 0);

    gtk_box_pack_start(section1, img1, 0, 0, 0);
    gtk_box_pack_start(section1, addBox, 0, 0, 0);

    gtk_box_pack_start(section2, changeBox, 0, 0, 0);
    gtk_box_pack_start(section2, img2, 0, 0, 0);

    gtk_box_pack_start(section3, img3, 0, 0, 0);
    gtk_box_pack_start(section3, updateBox, 0, 0, 0);

    gtk_widget_set_name(headerManage, "headerManage");

    containerMange = gtk_vbox_new(0, 5);
    gtk_widget_set_name(containerMange, "containerManage");

    gtk_box_pack_start(containerMange, headerManage, 0 , 0, 0);
    gtk_box_pack_end(containerMange, section1, 0 ,0 ,0);
    gtk_box_pack_end(containerMange, section2, 0 ,0 ,0);
    gtk_box_pack_end(containerMange, section3, 0 ,0 ,0);
    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Saler site");
	gtk_window_set_default_size(GTK_WINDOW(window),400, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, containerMange);
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
