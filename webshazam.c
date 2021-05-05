#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#include <future>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void
getScreenshotFunction(GObject *object,
                     GAsyncResult *result,
                     gpointer data)
{
    WebKitWebView * webview = (WebKitWebView*)data;
    GError* error = NULL;
	cairo_surface_t* surface = webkit_web_view_get_snapshot_finish(webview, result, &error);
	cairo_surface_write_to_png(surface, "/tmp/test.png");
}

static int startScreenshot(gpointer webView) {
    webkit_web_view_get_snapshot((WebKitWebView*)webView,
                                 WEBKIT_SNAPSHOT_REGION_FULL_DOCUMENT,
                                 WEBKIT_SNAPSHOT_OPTIONS_NONE,
                                 NULL,
                                 getScreenshotFunction,
                                 (WebKitWebView*)webView);
    return 0;
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 900, 600);

    WebKitWebContext* context = webkit_web_context_get_default();
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new_with_user_content_manager(webkit_user_content_manager_new()));

    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), GTK_WIDGET(webView));
    gtk_container_add(GTK_CONTAINER(main_window), scrolledWindow);
    webkit_web_view_load_uri(webView, "https://bbc.github.io/psammead/iframe.html?id=components-brand--without-brand-link&viewMode=story");
    gtk_widget_grab_focus(GTK_WIDGET(webView));
    gtk_widget_show_all(main_window);

    g_timeout_add_seconds(5, startScreenshot, webView);

    gtk_main();


    return 0;
}