/**
 * Martin Egli
 * 2024-01-02
 * case for LT1
 */
use <parts.scad> 

module lt1_m3holes_row(dia = 3.1, len1 = 1.6+2, loc_res = 32) {
    translate([5, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
    translate([32, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
    translate([83, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
    translate([138, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
    translate([185, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
    translate([240, 0, 0])
    cylinder(d = dia, h = len1, $fn = loc_res);
}

module lt1_single_led_display(hi1 = 9, loc_res = 32) {
    translate([0, 0, 0])
    cube([37.8, 53, hi1]);
}

module lt1_all_led_displays(nb_leds= 6, hi1 = 9, loc_res = 32) {
    for(n=[0:1:nb_leds-1])
        translate([n*37.8, 0, 0])
        lt1_single_led_display(hi1, loc_res);
}

module lt1_debug_header() {
    translate([0, 0, 0])
    cube([4.4, 9, 2.2+1]);
}

module lt1_pcb_components(th1 = 1.6, col = "LightGreen", loc_res = 32) {
    color(col) {
        difference() {
            hull() {
                translate([5, 5, 0])
                cylinder(r = 5, h = th1, $fn = loc_res);
                translate([240, 5, 0])
                cylinder(r = 5, h = th1, $fn = loc_res);
                translate([5, 71, 0])
                cylinder(r = 5, h = th1, $fn = loc_res);
                translate([240, 71, 0])
                cylinder(r = 5, h = th1, $fn = loc_res);
            }
            
            // M3 holes
            translate([0, 5, -1])
            lt1_m3holes_row();
            translate([0, 71, -1])
            lt1_m3holes_row();
            // cut away switch (NC)
            translate([194, 69, -1])
            cube([211-194, 77-69, th1+2]);
            // cut away debug header, 50 mil 
            translate([-1, 48, -1])
            cube([4, 57-48, th1+2]);
        }
    
        // all components
        translate([5.2, 11.5, th1])
        lt1_all_led_displays();
        translate([-1.4, 48, -1.4])
        lt1_debug_header();
        // buttons 1, 2, 3, 4
        translate([62, 5, th1])
        buttonTS0266_cut(show_origin=0);
        translate([107.6, 5, th1])
        buttonTS0266_cut(show_origin=0);
        translate([168.4, 5, th1])
        buttonTS0266_cut(show_origin=0);
        translate([214, 5, th1])
        buttonTS0266_cut(show_origin=0);
        // buttons play, mode, stop
        translate([240, 58, th1])
        buttonTS0266_cut(show_origin=0);
        translate([240, 38, th1])
        buttonTS0266_cut(show_origin=0);
        translate([240, 18, th1])
        buttonTS0266_cut(show_origin=0);
        // micro usb
        translate([-1.4, 33.5, -1.4])
        cube([5.5+1.4, 42.5-33.5, 2]);
        // battery
        translate([50, 30, -11])
        cube([48, 22, 11]);
    }
}

lt1_pcb_components();