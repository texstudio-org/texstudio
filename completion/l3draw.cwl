# l3draw package
# Matthew Bertucci 2025/06/30

\draw_set_baseline:n {%<⟨length⟩%>}#/%expl3
\draw_begin:#/%expl3
\draw_box_use:N %<⟨box⟩%>#/%expl3
\draw_box_use:Nn %<⟨box⟩%> {%<⟨point⟩%>}#/%expl3
\draw_set_cap_butt:#/%expl3
\draw_set_cap_rectangle:#/%expl3
\draw_set_cap_round:#/%expl3
\draw_coffin_use:Nnn %<⟨coffin⟩%> {%<⟨hpole⟩%>} {%<⟨vpole⟩%>}#/%expl3
\draw_coffin_use:Nnnn %<⟨coffin⟩%> {%<⟨hpole⟩%>} {%<⟨vpole⟩%>} {%<⟨point⟩%>}#/%expl3
\draw_set_dash_pattern:nn {%<⟨pattern⟩%>} {%<⟨phase⟩%>}#/%expl3
\draw_end:#/%expl3
\draw_set_evenodd_rule:#/%expl3
\draw_set_join_bevel:#/%expl3
\draw_set_join_miter:#/%expl3
\draw_set_join_round:#/%expl3
\draw_layer_begin:n {%<⟨layer⟩%>}#/%expl3
\draw_layer_end:#/%expl3
\draw_layer_new:n {%<⟨layer⟩%>}#/%expl3
\draw_set_linewidth:n {%<⟨width⟩%>}#/%expl3
\draw_set_miterlimit:n {%<⟨factor⟩%>}#/%expl3
\draw_set_nonzero_rule:#/%expl3
\draw_path_arc:nnn {%<⟨angle1⟩%>} {%<⟨angle2⟩%>} {%<⟨radius⟩%>}#/%expl3
\draw_path_arc:nnnn {%<⟨angle1⟩%>} {%<⟨angle2⟩%>} {%<⟨radius-a⟩%>} {%<⟨radius-b⟩%>}#/%expl3
\draw_path_arc_axes:nnn {%<⟨angle1⟩%>} {%<⟨angle2⟩%>} {%<⟨vector1⟩%>} {%<⟨vector2⟩%>}#/%expl3
\draw_path_canvas_curveto:nnn {%<⟨control1⟩%>} {%<⟨control2⟩%>} {%<⟨end⟩%>}#/%expl3
\draw_path_canvas_lineto:n {%<⟨canvas point⟩%>}#/%expl3
\draw_path_canvas_moveto:n {%<⟨canvas point⟩%>}#/%expl3
\draw_path_circle:nn {%<⟨center⟩%>} {%<⟨radius⟩%>}#/%expl3
\draw_path_close:#/%expl3
\draw_path_corner_arc:nn {%<⟨length1⟩%>} {%<⟨length2⟩%>}#/%expl3
\draw_path_curveto:nn {%<⟨control⟩%>} {%<⟨end⟩%>}#/%expl3
\draw_path_curveto:nnn {%<⟨control1⟩%>} {%<⟨control2⟩%>} {%<⟨end⟩%>}#/%expl3
\draw_path_ellipse:nnn {%<⟨center⟩%>} {%<⟨vector1⟩%>} {%<⟨vector2⟩%>}#/%expl3
\draw_path_grid:nnnn {%<⟨xstep⟩%>} {%<⟨ystep⟩%>} {%<⟨lower-left⟩%>} {%<⟨upper-right⟩%>}#/%expl3
\draw_path_lineto:n {%<⟨point⟩%>}#/%expl3
\draw_path_moveto:n {%<⟨point⟩%>}#/%expl3
\draw_path_rectangle:nn {%<⟨lower-left⟩%>} {%<⟨displacement⟩%>}#/%expl3
\draw_path_rectangle_corners:nn {%<⟨lower-left⟩%>} {%<⟨top-right⟩%>}#/%expl3
\draw_path_replace_bb:#/%expl3
\draw_path_scope_begin:#/%expl3
\draw_path_scope_end:#/%expl3
\draw_path_use:n {%<⟨action(s)⟩%>}#/%expl3
\draw_point_interpolate_curve:nnnnnn {%<⟨part⟩%>} {%<⟨start⟩%>} {%<⟨control1⟩%>} {%<⟨control2⟩%>} {%<⟨end⟩%>}#/%expl3
\draw_point_interpolate_distance:nnn {%<⟨distance⟩%>} {%<⟨point expr1⟩%>} {%<⟨point expr2⟩%>}#/%expl3
\draw_point_interpolate_line:nnn {%<⟨part⟩%>} {%<⟨point1⟩%>} {%<⟨point2⟩%>}#/%expl3
\draw_point_intersect_circles:nnnnn {%<⟨center1⟩%>} {%<⟨radius1⟩%>} {%<⟨center2⟩%>} {%<⟨radius2⟩%>} {%<⟨root⟩%>}#/%expl3
\draw_point_intersect_line_circle:nnnnn {%<⟨point1⟩%>} {%<⟨point2⟩%>} {%<⟨center⟩%>} {%<⟨radius⟩%>} {%<⟨root⟩%>}#/%expl3
\draw_point_intersect_lines:nnnn {%<⟨point1⟩%>} {%<⟨point2⟩%>} {%<⟨point3⟩%>} {%<⟨point4⟩%>}#/%expl3
\draw_point_polar:nn {%<⟨radius⟩%>} {%<⟨angle⟩%>}#/%expl3
\draw_point_polar:nnn {%<⟨radius-a⟩%>} {%<⟨radius-b⟩%>} {%<⟨angle⟩%>}#/%expl3
\draw_point_transform:n {%<⟨point⟩%>}#/%expl3
\draw_point_unit_vector:n {%<⟨point⟩%>}#/%expl3
\draw_point_vec:nn {%<⟨xscale⟩%>} {%<⟨yscale⟩%>}#/%expl3
\draw_point_vec:nnn {%<⟨xscale⟩%>} {%<⟨yscale⟩%>} {%<⟨zscale⟩%>}#/%expl3
\draw_point_vec_polar:nn {%<⟨radius⟩%>} {%<⟨angle⟩%>}#/%expl3
\draw_point_vec_polar:nnn {%<⟨radius-a⟩%>} {%<⟨radius-b⟩%>} {%<⟨angle⟩%>}#/%expl3
\draw_scope_begin:#/%expl3
\draw_scope_end:#/%expl3
\draw_suspend_begin:#/%expl3
\draw_suspend_end:#/%expl3
\draw_transform_matrix:nnnn {%<⟨a⟩%>} {%<⟨b⟩%>} {%<⟨c⟩%>} {%<⟨d⟩%>}#/%expl3
\draw_transform_matrix_absolute:nnnn {%<⟨a⟩%>} {%<⟨b⟩%>} {%<⟨c⟩%>} {%<⟨d⟩%>}#/%expl3
\draw_transform_matrix_invert:#/%expl3
\draw_transform_matrix_reset:#/%expl3
\draw_transform_rotate:n {%<⟨angle⟩%>}#/%expl3
\draw_transform_scale:n {%<⟨scale⟩%>}#/%expl3
\draw_transform_shift:n {%<⟨vector⟩%>}#/%expl3
\draw_transform_shift_absolute:n {%<⟨vector⟩%>}#/%expl3
\draw_transform_shift_invert:#/%expl3
\draw_transform_shift_reset:#/%expl3
\draw_transform_triangle:nnn {%<⟨origin⟩%>} {%<⟨point1⟩%>} {%<⟨point2⟩%>}#/%expl3
\draw_transform_xscale:n {%<⟨scale⟩%>}#/%expl3
\draw_transform_xshift:n {%<⟨shift⟩%>}#/%expl3
\draw_transform_xslant:n {%<⟨slant⟩%>}#/%expl3
\draw_transform_yscale:n {%<⟨scale⟩%>}#/%expl3
\draw_transform_yshift:n {%<⟨shift⟩%>}#/%expl3
\draw_transform_yslant:n {%<⟨slant⟩%>}#/%expl3
\draw_xvec:n {%<⟨point⟩%>}#/%expl3
\draw_yvec:n {%<⟨point⟩%>}#/%expl3
\draw_zvec:n {%<⟨point⟩%>}#/%expl3
\g_draw_bb_xmax_dim#/%expl3
\g_draw_bb_xmin_dim#/%expl3
\g_draw_bb_ymax_dim#/%expl3
\g_draw_bb_ymin_dim#/%expl3
\g_draw_id_int#/%expl3
\l_draw_bb_update_bool#/%expl3
\l_draw_default_linewidth_dim#/%expl3
\l_draw_layers_clist#/%expl3
