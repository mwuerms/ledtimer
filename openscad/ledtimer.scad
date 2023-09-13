/**
 * Martin Egli
 * 2023-09-13
 */
 
 use <parts.scad>

// - pcb and electronics --------------------------------------------------- 
 module pcbLT01_holes(loc_res = 32, hole_dia = 3, hole_height = 5) {
    translate([5, 5, 0])
    cylinder(d = hole_dia, h = hole_height, $fn = loc_res);
    translate([6*37.8+15, 5, 0])
    cylinder(d = hole_dia, h = hole_height, $fn = loc_res);
    translate([5, 53+20, 0])
    cylinder(d = hole_dia, h = hole_height, $fn = loc_res);
    translate([6*37.8+15, 53+20, 0])
    cylinder(d = hole_dia, h = hole_height, $fn = loc_res);
 }
 
 module pcbLT01(show_components = 1, loc_res = 32, pcb_th = 1.6) {
    if(show_components) {
        translate([37.8/2+5, 53/2+12, 0])
        for(n = [0:1:5])
        translate([n*37.7, 0, 0])
        ledsTC2011RWA(show_origin = 0);
        
        translate([2.5*7.62+5, 5, 0])
        buttonTS026695();
        translate([8.5*7.62+5, 5, 0])
        buttonTS026695();
        translate([16.5*7.62+5, 5, 0])
        buttonTS026695();
        translate([22.5*7.62+5, 5, 0])
        buttonTS026695();
        
        translate([6*37.8+11, (53+20)/2+15, 0])
        buttonTS026695();
        translate([6*37.8+11, (53+20)/2- 0, 0])
        buttonTS026695();
        translate([6*37.8+11, (53+20)/2-15, 0])
        buttonTS026695();
        
    }
    
    color("Green") {
        difference() {
            hull() {
                translate([5, 5, -pcb_th])
                cylinder(d = 10, h = pcb_th, $fn = loc_res);
                translate([6*37.8+15, 5, -pcb_th])
                cylinder(d = 10, h = pcb_th, $fn = loc_res);
                translate([5, 53+20, -pcb_th])
                cylinder(d = 10, h = pcb_th, $fn = loc_res);
                translate([6*37.8+15, 53+20, -pcb_th])
                cylinder(d = 10, h = pcb_th, $fn = loc_res);
            }
            translate([0, 0, -3])
            pcbLT01_holes(hole_dia = 3, hole_height = 5);
        }
    }
}

    
module pcbLT01_componentscut(show_components = 1, loc_res = 32, pcb_th = 1.6) {
    // components
    translate([37.8/2+5, 53/2+12, 0])
    for(n = [0:1:5])
    translate([n*37.7, 0, 0])
    ledsTC2011RWA_cut(show_origin = 0, cut_height = 20);
    
    translate([2.5*7.62+5, 5, 0])
    buttonTS0266_cut(12);
    translate([8.5*7.62+5, 5, 0])
    buttonTS0266_cut(12);
    translate([16.5*7.62+5, 5, 0])
    buttonTS0266_cut(12);
    translate([22.5*7.62+5, 5, 0])
    buttonTS0266_cut(12);
    
    translate([6*37.8+11, (53+20)/2+15, 0])
    buttonTS026695();
    translate([6*37.8+11, (53+20)/2- 0, 0])
    buttonTS026695();
    translate([6*37.8+11, (53+20)/2-15, 0])
    buttonTS026695();
    
    // M3 screws
}

// - 3d printed parts -----------------------

module caseTop(loc_res = 32/2) {
    color("LightBlue") {
        difference() {
            union() {
                difference() {
                    hull() {
                        translate([5, 5, 0]) {
                            translate([0, 0, 0])
                            cylinder(d = 10, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 10, $fn = loc_res);
                        }
                        translate([6*37.8+15, 5, 0]) {
                            translate([0, 0, 0])
                            cylinder(d = 10, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 10, $fn = loc_res);
                        }
                        translate([5, 53+20, 0]) {
                            translate([0, 0, 0])
                            cylinder(d = 10, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 10, $fn = loc_res);
                        }
                        translate([6*37.8+15, 53+20, 0]) {
                            translate([0, 0, 0])
                            cylinder(d = 10, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 10, $fn = loc_res);
                        }
                    }
                    
                    hull() {
                        translate([5, 5, -1])
                        cylinder(d = 12, h = 1, $fn = loc_res);
                        translate([6*37.8+15, 5, -1])
                        cylinder(d = 12, h = 1, $fn = loc_res);
                        translate([5, 53+20, -1])
                        cylinder(d = 12, h = 1, $fn = loc_res);
                        translate([6*37.8+15, 53+20, -1])
                        cylinder(d = 12, h = 1, $fn = loc_res);
                    }
                    hull() {
                        translate([5, 5, 0]) {
                            translate([0, 0, -1])
                            cylinder(d = 8, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 8, $fn = loc_res);
                        }
                        translate([6*37.8+15, 5, 0]) {
                            translate([0, 0, -1])
                            cylinder(d = 8, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 8, $fn = loc_res);
                        }
                        translate([5, 53+20, 0]) {
                            translate([0, 0, -1])
                            cylinder(d = 8, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 8, $fn = loc_res);
                        }
                        translate([6*37.8+15, 53+20, 0]) {
                            translate([0, 0, -1])
                            cylinder(d = 8, h = 1, $fn = loc_res);
                            translate([0, 0, 4])
                            sphere(d = 8, $fn = loc_res);
                        }
                    }
                    pcbLT01_componentscut();
                    // icons on the right
                    // play/pause
                    #translate([6*37.8+11, (53+20)/2+15+4, 8.5]) {
                        hull() {
                            translate([3, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([3, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                        hull() {
                            translate([1, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([1, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                        hull() {
                            translate([-4, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([-1, 2, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([-4, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                        
                    }
                    // next
                    #translate([6*37.8+11, (53+20)/2- 0+4, 8.5]) {
                        hull() {
                            translate([2, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([2, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                        hull() {
                            translate([-2.5, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([+1.5, 2, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([-2.5, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                        
                    }
                    
                    // stop
                    #translate([6*37.8+11, (53+20)/2-15+4, 8.5]) {
                        hull() {
                            translate([-2, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([-2, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([+2, 0, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                            translate([+2, 4, 0])
                            cylinder(d = 1, h = 1, $fn = loc_res);
                        }
                    }
                    
                    
                }
                translate([0, 0, 0])
                pcbLT01_holes(hole_dia = 5, hole_height = 8.2);
            }
            translate([0, 0, -1])
            pcbLT01_holes(hole_dia = 2.5, hole_height = 7+1);
        }
    }
}
caseTop();
*pcbLT01();
