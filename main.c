#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

void open_about(GtkWidget *box, gpointer layout);
void show_cheat_sheet(GtkWidget *box, gpointer data);
void destroy_cheat_sheet(GtkWidget *box, gpointer data);
void run_code(GtkWidget *box, gpointer text_view);
void file_open(GtkWidget *box, gpointer text_view);
void save_file(GtkWidget *box, gpointer text_view);

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *image;
    GtkCssProvider *css_provider;
    GtkWidget *header_bar;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;

    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 980, 700);
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "./img/book4.png", NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), true);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "StackEdit");
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

    image = gtk_image_new_from_file("./img/book.png");
    gtk_widget_set_name(image, "window_icon");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), image);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, 900, 700);
    gtk_widget_set_name(scrolled_window, "scrolled_window");
    gtk_layout_put(GTK_LAYOUT(layout), scrolled_window, 81, 0);

    text_view = gtk_text_view_new();
    gtk_widget_set_name(text_view, "text_view");
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/play.png");
    gtk_widget_set_tooltip_text(button, "Run");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "run");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(run_code), text_view);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), button);

    entry = gtk_entry_new();
    gtk_widget_set_size_request(entry, 200, 35);
    gtk_widget_set_name(entry, "project_name");
    gtk_entry_set_text(GTK_ENTRY(entry), "Untitled Project");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), entry);

    /* FILE SYSTEM TOOL BOX */

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_name(box, "tool_bar");
    gtk_layout_put(GTK_LAYOUT(layout), box, 0, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_icon_name("document-new", 5);
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "new");
    gtk_widget_set_tooltip_text(button, "New");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/folder.png");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "open");
    gtk_widget_set_tooltip_text(button, "Open");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(file_open), text_view);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/document.png");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "save");
    gtk_widget_set_tooltip_text(button, "Save");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/question.png");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "dialog-question");
    gtk_widget_set_tooltip_text(button, "Help");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_icon_name("help-about", 5);
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "help-about");
    gtk_widget_set_tooltip_text(button, "About");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(open_about), NULL);
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/user.png");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "user");
    gtk_widget_set_tooltip_text(button, "User");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_file("./img/settings.png");
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "settings");
    gtk_widget_set_tooltip_text(button, "Settings");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);

    /* FILE SYSTEM TOOL BOX */

    /* --------------------------------------------------------------------------------- */

    /* DOCUMENT EDITOR TOOL BOX */

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_name(box, "editor_box");
    gtk_layout_put(GTK_LAYOUT(layout), box, 900, 0);

    button = gtk_button_new();
    image = gtk_image_new_from_icon_name("emblem-documents", 5);
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "cheat-sheet");
    gtk_widget_set_tooltip_text(button, "Cheat-Sheet");
    gtk_box_pack_start(GTK_BOX(box), button, false, true, 0);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(show_cheat_sheet), layout);

    /* DOCUMENT EDITOR TOOL BOX */

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
};
