/**
 * Martin Egli
 * 2021-11-01
 * M3 screw cut outs
 */

module m3ScrewCut(len = 10, loc_res = 32) {
    translate([0, 0, 0])
    cylinder(d = 3.2, h = len, $fn = loc_res);
}

module m3SinkHeadCut(len = 4, loc_res = 32) {
    translate([0, 0, 0])
    cylinder(d1 = 3.2, d2 = 6.6, h = 2, $fn = loc_res);
    translate([0, 0, 2])
    cylinder(d = 6.6, h = len, $fn = loc_res);
}
module m3CylinderHeadCut(len = 4, loc_res = 32) {
    translate([0, 0, 0])
    cylinder(d = 6, h = len, $fn = loc_res);
}

module m3ScrewSinkHeadCut(len = 4, loc_res = 32) {
    translate([0, 0, 0])
    m3ScrewCut(len, loc_res);
    translate([0, 0, len])
    m3SinkHeadCut(len, loc_res);
}

module m3NutCut() {
    translate([0, 0, 0])
    cylinder(d = 6.6, h = 4, $fn = 6);
}

module m3SinkHeadScewNutCut(len = 10, loc_res = 32) {
    translate([0, 0, len])
    m3SinkHeadCut(4, loc_res);
    m3ScrewCut(len+1, loc_res);
    m3NutCut();
}

module m3CylinderHeadScewNutCut(len = 10, loc_res = 32) {
    translate([0, 0, len])
    m3CylinderHeadCut(4, loc_res);
    m3ScrewCut(len+1, loc_res);
    m3NutCut();
}

//m3SinkHeadScewNutCut(20);
//m3CylinderHeadScewNutCut(15);
m3ScrewSinkHeadCut(10);