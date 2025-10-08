/**
 * testing LED Timer 2
 * Martin Egli
 * 2025-10-6
 */

module led0603(col = "Red", loc_res = 32) {
    // lense
    color(col)
    translate([-1.1/2, -0.8/2, 0.2])
    cube([1.1, 0.8, 0.35]);
    color("LightGray")
    translate([-1.6/2, -0.8/2, 0])
    cube([1.6, 0.8, 0.2]);
}

module ledxy(x = 0, y = 0, col = "Red") {
    translate([x, y, 0])
    led0603(col = col);
}

module ledxy_cut6(x = 0, y = 0, height = 6, dia = 4.8) {
    translate([x, y, -1])
    cylinder(d = dia, h = height+2, $fn = 6);
}

module place_leds() {
    ledxy((0*4), -1*5);
    //ledxy((0*4), 0*5);
    //ledxy((0*4), 1*5);
    //ledxy((0*4), 2*5);
    //ledxy((0*4), 3*5);
    //ledxy((0*4), 4*5);
    //ledxy((0*4), 5*5);
    
    ledxy(-(1*4), 0*5+5/2);
    ledxy(-(1*4), 1*5+5/2);
    ledxy(-(1*4), 2*5+5/2);
    ledxy(-(1*4), 3*5+5/2);
    //ledxy(-(1*4), 4*5+5/2);
    
    ledxy(-(2*4), 0*5);
    //ledxy(-(2*4), 1*5);
    ledxy(-(2*4), 2*5);
    //ledxy(-(2*4), 3*5);
    ledxy(-(2*4), 4*5);
    //ledxy(-(2*4), 5*5);
    
    ledxy(-(3*4), 0*5+5/2);
    ledxy(-(3*4), 1*5+5/2);
    ledxy(-(3*4), 2*5+5/2);
    ledxy(-(3*4), 3*5+5/2);
    //ledxy(-(1*4), 4*5+5/2);
    
    ledxy(+(1*4), 0*5+5/2);
    ledxy(+(1*4), 1*5+5/2);
    ledxy(+(1*4), 2*5+5/2);
    ledxy(+(1*4), 3*5+5/2);
    //ledxy(+(1*4), 4*5+5/2);
    
    ledxy(+(2*4), 0*5);
    //ledxy(+(2*4), 1*5);
    ledxy(+(2*4), 2*5);
    //ledxy(+(2*4), 3*5);
    ledxy(+(2*4), 4*5);
    //ledxy(+(2*4), 5*5);
    
    ledxy(+(3*4), 0*5+5/2);
    ledxy(+(3*4), 1*5+5/2);
    ledxy(+(3*4), 2*5+5/2);
    ledxy(+(3*4), 3*5+5/2);
    //ledxy(+(1*4), 4*5+5/2);
}

module place_led_cuts() {
    ledxy_cut6((0*4), -1*5);
    //ledxy_cut6((0*4), 0*5);
    //ledxy_cut6((0*4), 1*5);
    //ledxy_cut6((0*4), 2*5);
    //ledxy_cut6((0*4), 3*5);
    //ledxy_cut6((0*4), 4*5);
    //ledxy_cut6((0*4), 5*5);
    
    ledxy_cut6(-(1*4), 0*5+5/2);
    ledxy_cut6(-(1*4), 1*5+5/2);
    ledxy_cut6(-(1*4), 2*5+5/2);
    ledxy_cut6(-(1*4), 3*5+5/2);
    //ledxy_cut6(-(1*4), 4*5+5/2);
    
    ledxy_cut6(-(2*4), 0*5);
    //ledxy_cut6(-(2*4), 1*5);
    ledxy_cut6(-(2*4), 2*5);
    //ledxy_cut6(-(2*4), 3*5);
    ledxy_cut6(-(2*4), 4*5);
    //ledxy_cut6(-(2*4), 5*5);
    
    ledxy_cut6(-(3*4), 0*5+5/2);
    ledxy_cut6(-(3*4), 1*5+5/2);
    ledxy_cut6(-(3*4), 2*5+5/2);
    ledxy_cut6(-(3*4), 3*5+5/2);
    //ledxy_cut6(-(1*4), 4*5+5/2);
    
    ledxy_cut6(+(1*4), 0*5+5/2);
    ledxy_cut6(+(1*4), 1*5+5/2);
    ledxy_cut6(+(1*4), 2*5+5/2);
    ledxy_cut6(+(1*4), 3*5+5/2);
    //ledxy_cut6(+(1*4), 4*5+5/2);
    
    ledxy_cut6(+(2*4), 0*5);
    //ledxy_cut6(+(2*4), 1*5);
    ledxy_cut6(+(2*4), 2*5);
    //ledxy_cut6(+(2*4), 3*5);
    ledxy_cut6(+(2*4), 4*5);
    //ledxy_cut6(+(2*4), 5*5);
    
    ledxy_cut6(+(3*4), 0*5+5/2);
    ledxy_cut6(+(3*4), 1*5+5/2);
    ledxy_cut6(+(3*4), 2*5+5/2);
    ledxy_cut6(+(3*4), 3*5+5/2);
    //ledxy_cut6(+(1*4), 4*5+5/2);
}

place_leds();
difference() {
    translate([0, 10, 0])
    cylinder(d = 36, h = 4, $fn = 128);
    place_led_cuts();
}