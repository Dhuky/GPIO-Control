set(component_srcs "src/gpio_ctrl.cpp")

idf_component_register(SRCS "${component_srcs}"
                       PRIV_REQUIRES driver esp_log
                       INCLUDE_DIRS "include")