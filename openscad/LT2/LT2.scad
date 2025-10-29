/**
 * testing LED Timer 2
 * Martin Egli
 * 2025-10-6
 */

use <parts.scad>

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
    translate([x, y, 0])
    cylinder(d = dia, h = height, $fn = 6);
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

module place_led_cuts(h1 = 4) {
    ledxy_cut6((0*4), -1*5, height = h1);
    //ledxy_cut6((0*4), 0*5, height = h1);
    //ledxy_cut6((0*4), 1*5, height = h1);
    //ledxy_cut6((0*4), 2*5, height = h1);
    //ledxy_cut6((0*4), 3*5, height = h1);
    //ledxy_cut6((0*4), 4*5, height = h1);
    //ledxy_cut6((0*4), 5*5, height = h1);
    
    ledxy_cut6(-(1*4), 0*5+5/2, height = h1);
    ledxy_cut6(-(1*4), 1*5+5/2, height = h1);
    ledxy_cut6(-(1*4), 2*5+5/2, height = h1);
    ledxy_cut6(-(1*4), 3*5+5/2, height = h1);
    //ledxy_cut6(-(1*4), 4*5+5/2, height = h1);
    
    ledxy_cut6(-(2*4), 0*5, height = h1);
    //ledxy_cut6(-(2*4), 1*5, height = h1);
    ledxy_cut6(-(2*4), 2*5, height = h1);
    //ledxy_cut6(-(2*4), 3*5, height = h1);
    ledxy_cut6(-(2*4), 4*5, height = h1);
    //ledxy_cut6(-(2*4), 5*5, height = h1);
    
    ledxy_cut6(-(3*4), 0*5+5/2, height = h1);
    ledxy_cut6(-(3*4), 1*5+5/2, height = h1);
    ledxy_cut6(-(3*4), 2*5+5/2, height = h1);
    ledxy_cut6(-(3*4), 3*5+5/2, height = h1);
    //ledxy_cut6(-(1*4), 4*5+5/2, height = h1);
    
    ledxy_cut6(+(1*4), 0*5+5/2, height = h1);
    ledxy_cut6(+(1*4), 1*5+5/2, height = h1);
    ledxy_cut6(+(1*4), 2*5+5/2, height = h1);
    ledxy_cut6(+(1*4), 3*5+5/2, height = h1);
    //ledxy_cut6(+(1*4), 4*5+5/2);
    
    ledxy_cut6(+(2*4), 0*5, height = h1);
    //ledxy_cut6(+(2*4), 1*5, height = h1);
    ledxy_cut6(+(2*4), 2*5, height = h1);
    //ledxy_cut6(+(2*4), 3*5, height = h1);
    ledxy_cut6(+(2*4), 4*5, height = h1);
    //ledxy_cut6(+(2*4), 5*5, height = h1);
    
    ledxy_cut6(+(3*4), 0*5+5/2, height = h1);
    ledxy_cut6(+(3*4), 1*5+5/2, height = h1);
    ledxy_cut6(+(3*4), 2*5+5/2, height = h1);
    ledxy_cut6(+(3*4), 3*5+5/2, height = h1);
    //ledxy_cut6(+(1*4), 4*5+5/2, height = h1);
}

module pcb(dia1 = 38.5, th1 = 1.6, loc_res = 32) {
    // pcb
    color("Green")
    difference() {
        translate([0, 10, -(th1+0.01)])
        cylinder(d = dia1, h = th1, $fn = loc_res);
        translate([-30/2, 23, -(th1+1)])
        cube([30, 10, th1+2]);
    }
    // leds
    translate([0, 0, 0])
    place_leds();
    // akku/battery
    *color("Silver")
    translate([-35.6/2, 1, -6])
    cube([35.6, 18, 4.5]);
    //rotary encoder
    translate([0, 23, -2])
    rotate([-90, 0, 0])
    rotary_encoder_pec11s_929k(loc_res = loc_res);
    // USB
    color("Silver") 
    hull() {
        translate([-3, -2, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3, h = 8, $fn = loc_res);
        translate([+3, -2, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3, h = 8, $fn = loc_res);
    }
}

module case_top(dia1 = 39, dia2 = 45, th1 = 4, loc_res = 32) {
    difference() {
        union() {
            translate([0, 10, 0.4])
            cylinder(d1 = dia2, d2 = dia1, h = th1, $fn = loc_res);
            translate([0, 10, -2])
            cylinder(d = dia2, h = 2.4, $fn = loc_res);
        }
        // cut LEDs
        translate([0, 0, -1])
        place_led_cuts(h1 = th1+1);
        // cut PCB
        translate([0, 10, -3])
        cylinder(d = 39, h = 3, $fn = loc_res);
        // cut encoder
        translate([-18/2, 23-0.2, -2])
        cube([18, 4.7, 6]);
        translate([0, 26, -2])
        rotate([-90, 0, 0])
        cylinder(d = 7.4, h = 8, $fn = loc_res);
        // cut USB C
        hull() {
            translate([-3, -2, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 3.5, h = 18, $fn = loc_res);
            translate([+3.5, -2, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 3.5, h = 18, $fn = loc_res);
        }
        hull() {
            translate([-3, -10, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 7, h = 18, $fn = loc_res);
            translate([+3.5, -10, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 7, h = 18, $fn = loc_res);
        }
        
        // see inside
        *translate([0, 0, -20])
        cube(40);
    }
}

module case_bottom(dia1 = 39, dia2 = 45, th1 = 4, loc_res = 32) {
    
    difference() {
        union() {
            translate([0, 10, -8.6])
            cylinder(d1 = dia1, d2 = dia2, h = th1, $fn = loc_res);
            translate([0, 10, -4.6])
            cylinder(d = dia2, h = 2.6, $fn = loc_res);
        }
        // cut PCB
        difference() {
            translate([0, 10, -7.6])
            cylinder(d = 38, h = 8, $fn = loc_res);
            translate([-30/2, 23, -8])
            cube([30, 10, 10]);
        }
        // cut battery
        translate([-36/2, 1, -7.6])
        cube([36, 18, 8]);
        // cut encoder
        translate([-18/2, 23-0.2, -8])
        cube([18, 4.7, 8]);
        translate([0, 26, -2])
        rotate([-90, 0, 0])
        cylinder(d = 7.4, h = 8, $fn = loc_res);
        // cut USB C
        hull() {
            translate([-3, -2, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 3.5, h = 18, $fn = loc_res);
            translate([+3.5, -2, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 3.5, h = 18, $fn = loc_res);
        }
        hull() {
            translate([-3, -10, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 7, h = 18, $fn = loc_res);
            translate([+3.5, -10, -(1.6+3/2)])
            rotate([90, 0, 0])
            cylinder(d = 7, h = 18, $fn = loc_res);
        }
        
        // see inside
        *translate([0, 0, -20])
        cube(40);
    }
}

*pcb();
case_top(loc_res = 128); // print 1 x
*case_bottom(loc_res = 128); // print 1 x
