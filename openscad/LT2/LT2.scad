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
    // mark origin/center
    color("Red") {
        translate([-1/2, -0.2/2, 0])
        cube([1, 0.2, 0.2]);
        translate([-0.2/2, -1/2, 0])
        cube([0.2, 1, 0.2]);
    }    
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

module pcb(loc_res = 32) {
    // pcb
    color("Green")
    difference() {
        translate([0, 0, -(1.6+0.01)])
        cylinder(d = 39, h = 1.6, $fn = loc_res);
        translate([-39/2, -39/2+34, -(1.6+1)])
        cube([39, 34, 1.6+2]);
    }
    // leds
    translate([0, -8.4, 0])
    place_leds();
    // akku/battery
    color("Silver")
    translate([-35.6/2, -18/2, -6])
    cube([35.6, 18, 4.5]);
    //rotary encoder
    translate([0, -39/2+34, -2])
    rotate([-90, 0, 0])
    rotary_encoder_pec11s_929k(loc_res = loc_res);
    // USB
    color("Silver")
    translate([0, -39/2+8, 0])
    hull() {
        translate([-3, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3, h = 8, $fn = loc_res);
        translate([+3, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3, h = 8, $fn = loc_res);
    }
    // vibra motor
    translate([-10, -14.4, -1.6])
    rotate([180, 0, 135])
    vibra_motor();
}

module pcb_cut(loc_res = 32) {
    // cut pcb
    difference() {
        translate([0, 0, -(2.1)])
        cylinder(d = 40, h = 2.3, $fn = loc_res);
        translate([-39.6/2, -39/2+34, -(1.6+1)])
        cube([39, 34.2, 1.6+2]);
    }
    // cut space beneath pcb
    translate([0, 0, -7])
    cylinder(d = 38, h = 6.7, $fn = loc_res);
    // cut LEDs
    translate([0, -8.4, -1])
    place_led_cuts(h1 = 4+1);
    // cut akku/battery
    translate([-36/2, -20/2, -7])
    cube([36, 20, 7.0]);
    // cut rotary encoder
    translate([0, -39/2+34-0.2, -2])
    rotate([-90, 0, 0])
    rotary_encoder_pec11s_929k_cut(loc_res = loc_res);
    // cut USB C
    translate([0, -39/2+8, 0])
    hull() {
        translate([-3, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3.5, h = 18, $fn = loc_res);
        translate([+3.5, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 3.5, h = 18, $fn = loc_res);
    }
    translate([0, -39/2-1, 0])
    hull() {
        translate([-3, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 7, h = 18, $fn = loc_res);
        translate([+3.5, 0, -(1.6+3/2)])
        rotate([90, 0, 0])
        cylinder(d = 7, h = 18, $fn = loc_res);
    }
    // vibra motor
    translate([-10, -14.4, -2.0])
    rotate([180, 0, 135])
    vibra_motor_cut(loc_res = loc_res);
}

module case_top(dia1 = 43, dia2 = 50, th1 = 4, loc_res = 32) {
    difference() {
        union() {
            translate([0, 0, 0.4])
            cylinder(d1 = dia2, d2 = dia1, h = th1, $fn = loc_res);
            translate([0, 0, -2])
            cylinder(d = dia2, h = 2.4, $fn = loc_res);
            
        }
        // cut pcb and components
        translate([0, 0, 0])
        pcb_cut();
        
        // see inside
        *translate([0, 0, -20])
        cube(40);
    }
}

module case_bottom(dia1 = 43, dia2 = 50, th1 = 4, loc_res = 32) {
    
    difference() {
        union() {
            translate([0, 0, -8.6])
            cylinder(d1 = dia1, d2 = dia2, h = th1, $fn = loc_res);
            translate([0, 0, -4.6])
            cylinder(d = dia2, h = 2.6, $fn = loc_res);
        }
        // cut pcb and components
        translate([0, 0, 0])
        pcb_cut();
        
        // see inside
        *translate([0, 0, -20])
        cube(40);
    }
}

*pcb();
*pcb_cut();
*case_top(loc_res = 128); // print 1 x
case_bottom(loc_res = 128); // print 1 x
