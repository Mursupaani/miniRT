/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_new_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2026/01/21 11:04:40 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	g_tests_passed = 0;
static int	g_tests_total = 0;

static void	print_separator(void)
{
	printf("\n========================================\n\n");
}

static void	print_test_header(const char *test_name)
{
	printf("\nTEST: %s\n", test_name);
	printf("====================\n\n");
}

__attribute__((unused))
static void	assert_double_eq(double actual, double expected, const char *msg)
{
	g_tests_total++;
	if (fabs(actual - expected) < EPSILON)
	{
		printf("✓ %s: %.6f == %.6f\n", msg, actual, expected);
		g_tests_passed++;
	}
	else
		printf("✗ %s: %.6f != %.6f\n", msg, actual, expected);
}

__attribute__((unused))
static void	assert_color_eq(t_color actual, t_color expected, const char *msg)
{
	g_tests_total++;
	if (fabs(actual.r - expected.r) < EPSILON &&
		fabs(actual.g - expected.g) < EPSILON &&
		fabs(actual.b - expected.b) < EPSILON)
	{
		printf("✓ %s: (%.2f, %.2f, %.2f)\n", msg, actual.r, actual.g, actual.b);
		g_tests_passed++;
	}
	else
	{
		printf("✗ %s: Expected (%.2f, %.2f, %.2f), got (%.2f, %.2f, %.2f)\n",
			msg, expected.r, expected.g, expected.b,
			actual.r, actual.g, actual.b);
	}
}

__attribute__((unused))
static void	assert_point_eq(t_point actual, t_point expected, const char *msg)
{
	g_tests_total++;
	if (fabs(actual.x - expected.x) < EPSILON &&
		fabs(actual.y - expected.y) < EPSILON &&
		fabs(actual.z - expected.z) < EPSILON)
	{
		printf("✓ %s: (%.2f, %.2f, %.2f)\n", msg, actual.x, actual.y, actual.z);
		g_tests_passed++;
	}
	else
	{
		printf("✗ %s: Expected (%.2f, %.2f, %.2f), got (%.2f, %.2f, %.2f)\n",
			msg, expected.x, expected.y, expected.z,
			actual.x, actual.y, actual.z);
	}
}

static void	test_ambient_light_parsing(void)
{
	print_test_header("Ambient Light Parsing");
	
	printf("Scenario: Parse ambient lighting independently\n");
	printf("Given a scene with ambient light defined first\n");
	printf("When parsing: 'A 0.2 255,255,255'\n");
	printf("Then ambient_ratio should be 0.2\n");
	printf("And ambient_color should be (1, 1, 1)\n\n");

	// This would need a mock app structure to test properly
	// For demonstration purposes:
	printf("Manual Test Required:\n");
	printf("  Create test.rt with: A 0.2 255,255,255\n");
	printf("  Verify light->ambient_ratio == 0.2\n");
	printf("  Verify light->ambient_color == color(1, 1, 1)\n");
	
	print_separator();
}

static void	test_light_with_ambient_parsing(void)
{
	print_test_header("Light After Ambient Parsing");
	
	printf("Scenario: Parse light after ambient\n");
	printf("Given a scene with:\n");
	printf("  A 0.2 255,255,255\n");
	printf("  L -40,50,0 0.6 255,255,255\n");
	printf("Then light should have both ambient and position/intensity\n\n");

	printf("Manual Test Required:\n");
	printf("  Create test.rt with both A and L lines\n");
	printf("  Verify both ambient and light data are preserved\n");
	
	print_separator();
}

static void	test_cube_parsing(void)
{
	print_test_header("Cube Parsing");
	
	printf("Scenario: Parse a cube object\n");
	printf("Given cube definition: 'cu 0,0,0 0,1,0 2.0 4.0 255,0,0'\n");
	printf("When parsing the cube\n");
	printf("Then position should be (0, 0, 0)\n");
	printf("And axis should be (0, 1, 0)\n");
	printf("And diameter should be 2.0\n");
	printf("And height should be 4.0\n");
	printf("And color should be red (1, 0, 0)\n\n");

	printf("Manual Test Required:\n");
	printf("  Create test.rt with: cu 0,0,0 0,1,0 2.0 4.0 255,0,0\n");
	printf("  Verify cube is created with correct parameters\n");
	printf("  Verify cube renders correctly in scene\n");
	
	print_separator();
}

static void	test_cone_parsing(void)
{
	print_test_header("Cone Parsing");
	
	printf("Scenario: Parse a cone object\n");
	printf("Given cone definition: 'co 5,0,-10 0,1,0 3.0 6.0 0,255,0'\n");
	printf("When parsing the cone\n");
	printf("Then position should be (5, 0, -10)\n");
	printf("And axis should be (0, 1, 0)\n");
	printf("And diameter should be 3.0\n");
	printf("And height should be 6.0\n");
	printf("And color should be green (0, 1, 0)\n\n");

	printf("Manual Test Required:\n");
	printf("  Create test.rt with: co 5,0,-10 0,1,0 3.0 6.0 0,255,0\n");
	printf("  Verify cone is created with correct parameters\n");
	printf("  Verify cone renders correctly in scene\n");
	printf("  Verify cone has minimum/maximum set correctly\n");
	printf("  Verify cone is closed\n");
	
	print_separator();
}

static void	test_texture_path_parsing(void)
{
	print_test_header("Texture Path Parsing");
	
	printf("Scenario: Parse texture path from string\n");
	printf("Given string: 'texture:path/to/file.png rest'\n");
	printf("When parsing texture\n");
	printf("Then path should be 'path/to/file.png'\n");
	printf("And remaining string should be ' rest'\n\n");

	printf("Manual Test Required:\n");
	printf("  Test with: sp 0,0,0 2.0 255,0,0 texture:Textures/earth.png\n");
	printf("  Verify texture is loaded and applied to sphere\n");
	printf("  Verify texture is freed on cleanup\n");
	
	print_separator();
}

static void	test_cube_textures_parsing(void)
{
	print_test_header("Cube Textures Parsing");
	
	printf("Scenario: Parse 6 texture paths for cube faces\n");
	printf("Given string: 'texture_cube:f.png,b.png,l.png,r.png,u.png,d.png'\n");
	printf("When parsing cube textures\n");
	printf("Then all 6 textures should be loaded\n");
	printf("And applied to respective cube faces\n\n");

	printf("Manual Test Required:\n");
	printf("  Create cube with 6 different textures\n");
	printf("  Verify each face has correct texture\n");
	printf("  Verify textures are mapped correctly\n");
	
	print_separator();
}

static void	test_bump_map_parsing(void)
{
	print_test_header("Bump Map Parsing");
	
	printf("Scenario: Parse bump map for object\n");
	printf("Given string: 'bump:Textures/bump.png'\n");
	printf("When parsing bump map\n");
	printf("Then bump_map texture should be loaded\n");
	printf("And has_bump_map should be true\n");
	printf("And uv_map function should be set\n\n");

	printf("Manual Test Required:\n");
	printf("  Test with: sp 0,0,0 2.0 255,0,0 bump:Textures/bump.png\n");
	printf("  Verify bump map is loaded\n");
	printf("  Verify bump map affects surface normals\n");
	printf("  Verify bump map is freed on cleanup\n");
	
	print_separator();
}

static void	test_combined_texture_and_bump(void)
{
	print_test_header("Combined Texture and Bump Map");
	
	printf("Scenario: Parse object with both texture and bump map\n");
	printf("Given: 'sp 0,0,0 2.0 255,0,0 texture:earth.png bump:earth_bump.png'\n");
	printf("When parsing sphere\n");
	printf("Then both texture and bump map should be applied\n");
	printf("And both should use spherical_map for UV mapping\n\n");

	printf("Manual Test Required:\n");
	printf("  Create sphere with both texture and bump map\n");
	printf("  Verify texture is visible\n");
	printf("  Verify bump mapping creates surface detail\n");
	printf("  Verify both work together correctly\n");
	
	print_separator();
}

static void	test_multiple_objects_with_features(void)
{
	print_test_header("Multiple Objects with Different Features");
	
	printf("Scenario: Parse scene with multiple object types\n");
	printf("Given scene with:\n");
	printf("  - Sphere with texture\n");
	printf("  - Cube with 6 textures\n");
	printf("  - Cylinder with bump map\n");
	printf("  - Cone with color only\n");
	printf("  - Plane with checkerboard pattern\n");
	printf("When parsing the complete scene\n");
	printf("Then all objects should be created correctly\n");
	printf("And each should have its features applied\n\n");

	printf("Manual Test Required:\n");
	printf("  Create comprehensive test.rt file\n");
	printf("  Verify all objects render correctly\n");
	printf("  Verify no memory leaks\n");
	
	print_separator();
}

static void	test_error_handling(void)
{
	print_test_header("Error Handling");
	
	printf("Scenario: Invalid texture path\n");
	printf("  Should display error: 'Failed to load texture'\n\n");
	
	printf("Scenario: Invalid bump map path\n");
	printf("  Should display error: 'Failed to load bump map'\n\n");
	
	printf("Scenario: Multiple ambient definitions\n");
	printf("  Should display error: 'Multiple ambient lighting definitions'\n\n");
	
	printf("Scenario: Multiple lights defined\n");
	printf("  Should display error: 'Multiple lights defined'\n\n");
	
	printf("Manual Test Required:\n");
	printf("  Test each error condition\n");
	printf("  Verify appropriate error messages\n");
	printf("  Verify program exits gracefully\n");
	
	print_separator();
}

void	test_new_parsing(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║  New Parsing Features Test Suite      ║\n");
	printf("╚════════════════════════════════════════╝\n");
	
	test_ambient_light_parsing();
	test_light_with_ambient_parsing();
	test_cube_parsing();
	test_cone_parsing();
	test_texture_path_parsing();
	test_cube_textures_parsing();
	test_bump_map_parsing();
	test_combined_texture_and_bump();
	test_multiple_objects_with_features();
	test_error_handling();
	
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║  Test Summary                          ║\n");
	printf("╚════════════════════════════════════════╝\n");
	printf("\nTests passed: %d/%d\n", g_tests_passed, g_tests_total);
	printf("\nNote: Most tests require manual verification with\n");
	printf("actual .rt scene files and visual inspection.\n");
	printf("\nSample test scene file (test_new_features.rt):\n");
	printf("--------------------------------------------\n");
	printf("A 0.2 255,255,255\n");
	printf("L -40,50,0 0.6 255,255,255\n");
	printf("C -50,0,20 0,0,1 70\n\n");
	printf("# Basic colored objects\n");
	printf("sp 0,0,-20 12.6 10,0,255\n");
	printf("pl 0,-10,0 0,1,0 255,255,255\n");
	printf("cy 10,0,-20 0,1,0 2.0 8.0 0,255,0\n\n");
	printf("# New object types\n");
	printf("cu -10,0,-20 0,1,0 4.0 4.0 200,100,50\n");
	printf("co 0,10,-20 0,1,0 3.0 6.0 255,255,0\n\n");
	printf("# With textures (requires texture files)\n");
	printf("# sp 5,0,-15 5.0 255,0,0 texture:Textures/earth.png\n");
	printf("# sp -5,0,-15 5.0 0,255,0 texture:Textures/moon.png bump:Textures/moon_bump.png\n");
	printf("# cu 0,5,-20 0,1,0 3.0 3.0 255,0,0 texture_cube:f.png,b.png,l.png,r.png,u.png,d.png\n");
	printf("--------------------------------------------\n\n");
}
