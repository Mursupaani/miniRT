/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhana <juhana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by juhana            #+#    #+#             */
/*   Updated: 2025/12/18 15:35:36 by juhana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	g_tests_passed = 0;
static int	g_tests_total = 0;

static void	print_separator(void)
{
	printf("\n========================================\n\n");
}

static void	test_parse_double(void)
{
	char	*str;
	char	*original;
	double	result;
	bool	success;

	printf("TEST: parse_double()\n");
	printf("====================\n\n");

	// Test 1: Parse positive integer
	str = "42 rest";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %.6f\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && result == 42.0)
		g_tests_passed++;

	// Test 2: Parse negative integer
	str = "-42 rest";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %.6f\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && result == -42.0)
		g_tests_passed++;

	// Test 3: Parse positive decimal
	str = "3.14159 rest";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %.6f\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(result - 3.14159) < 0.00001)
		g_tests_passed++;

	// Test 4: Parse negative decimal
	str = "-2.71828 rest";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %.6f\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(result - (-2.71828)) < 0.00001)
		g_tests_passed++;

	// Test 5: Parse with leading whitespace
	str = "   123.456 rest";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %.6f\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(result - 123.456) < 0.001)
		g_tests_passed++;

	// Test 6: Invalid input (no number)
	str = "not_a_number";
	original = str;
	success = parse_double(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Remaining: \"%s\"\n", str);
	g_tests_total++;
	if (!success)
		g_tests_passed++;

	print_separator();
}

static void	test_parse_int(void)
{
	char	*str;
	char	*original;
	int		result;
	bool	success;

	printf("TEST: parse_int()\n");
	printf("=================\n\n");

	// Test 1: Parse positive integer
	str = "255 rest";
	original = str;
	success = parse_int(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %d\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && result == 255)
		g_tests_passed++;

	// Test 2: Parse zero
	str = "0 rest";
	original = str;
	success = parse_int(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %d\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && result == 0)
		g_tests_passed++;

	// Test 3: Parse with whitespace
	str = "  128  rest";
	original = str;
	success = parse_int(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed value: %d\n", result);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && result == 128)
		g_tests_passed++;

	// Test 4: Invalid input
	str = "not_a_number";
	original = str;
	success = parse_int(&str, &result);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Remaining: \"%s\"\n", str);
	g_tests_total++;
	if (!success)
		g_tests_passed++;

	print_separator();
}

static void	test_parse_vector(void)
{
	char		*str;
	char		*original;
	t_vector	vec;
	bool		success;

	printf("TEST: parse_vector()\n");
	printf("====================\n\n");

	// Test 1: Parse vector with commas
	str = "1.0,2.0,3.0 rest";
	original = str;
	success = parse_vector(&str, &vec);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed vector: ");
	print_tuple(vec);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(vec.x - 1.0) < 0.001 && fabs(vec.y - 2.0) < 0.001 && fabs(vec.z - 3.0) < 0.001)
		g_tests_passed++;

	// Test 2: Parse vector without commas
	str = "0 1.0 0 rest";
	original = str;
	success = parse_vector(&str, &vec);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed vector: ");
	print_tuple(vec);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(vec.x - 0.0) < 0.001 && fabs(vec.y - 1.0) < 0.001 && fabs(vec.z - 0.0) < 0.001)
		g_tests_passed++;

	// Test 3: Parse normalized vector
	str = "-1.0,0.0,1.0";
	original = str;
	success = parse_vector(&str, &vec);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed vector: ");
	print_tuple(vec);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(vec.x - (-1.0)) < 0.001 && fabs(vec.y - 0.0) < 0.001 && fabs(vec.z - 1.0) < 0.001)
		g_tests_passed++;

	// Test 4: Parse vector with whitespace
	str = "  1.0 ,  2.0 ,  3.0  ";
	original = str;
	success = parse_vector(&str, &vec);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed vector: ");
	print_tuple(vec);
	printf("Remaining: \"%s\"\n", str);
	g_tests_total++;
	if (success && fabs(vec.x - 1.0) < 0.001 && fabs(vec.y - 2.0) < 0.001 && fabs(vec.z - 3.0) < 0.001)
		g_tests_passed++;

	print_separator();
}

static void	test_parse_point(void)
{
	char		*str;
	char		*original;
	t_point		pt;
	bool		success;

	printf("TEST: parse_point()\n");
	printf("===================\n\n");

	// Test 1: Parse point with commas
	str = "0.0,0.0,20.0 rest";
	original = str;
	success = parse_point(&str, &pt);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed point: ");
	print_tuple(pt);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(pt.x - 0.0) < 0.001 && fabs(pt.y - 0.0) < 0.001 && fabs(pt.z - 20.0) < 0.001)
		g_tests_passed++;

	// Test 2: Parse point without commas
	str = "-50 0 20 rest";
	original = str;
	success = parse_point(&str, &pt);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed point: ");
	print_tuple(pt);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(pt.x - (-50.0)) < 0.001 && fabs(pt.y - 0.0) < 0.001 && fabs(pt.z - 20.0) < 0.001)
		g_tests_passed++;

	// Test 3: Parse point with decimal values
	str = "50.123,-10.456,30.789";
	original = str;
	success = parse_point(&str, &pt);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed point: ");
	print_tuple(pt);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(pt.x - 50.123) < 0.001 && fabs(pt.y - (-10.456)) < 0.001 && fabs(pt.z - 30.789) < 0.001)
		g_tests_passed++;

	// Test 4: Parse point with whitespace
	str = "  10.0 ,  20.0 ,  30.0  ";
	original = str;
	success = parse_point(&str, &pt);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed point: ");
	print_tuple(pt);
	printf("Remaining: \"%s\"\n", str);
	g_tests_total++;
	if (success && fabs(pt.x - 10.0) < 0.001 && fabs(pt.y - 20.0) < 0.001 && fabs(pt.z - 30.0) < 0.001)
		g_tests_passed++;

	print_separator();
}

static void	test_parse_color(void)
{
	char		*str;
	char		*original;
	t_color		color;
	bool		success;

	printf("TEST: parse_color()\n");
	printf("===================\n\n");

	// Test 1: Parse white color
	str = "255,255,255 rest";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(color.r - 1.0) < 0.001 && fabs(color.g - 1.0) < 0.001 && fabs(color.b - 1.0) < 0.001)
		g_tests_passed++;

	// Test 2: Parse red color
	str = "255,0,0";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(color.r - 1.0) < 0.001 && fabs(color.g - 0.0) < 0.001 && fabs(color.b - 0.0) < 0.001)
		g_tests_passed++;

	// Test 3: Parse green color
	str = "0,255,0";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(color.r - 0.0) < 0.001 && fabs(color.g - 1.0) < 0.001 && fabs(color.b - 0.0) < 0.001)
		g_tests_passed++;

	// Test 4: Parse blue color
	str = "0,0,255";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(color.r - 0.0) < 0.001 && fabs(color.g - 0.0) < 0.001 && fabs(color.b - 1.0) < 0.001)
		g_tests_passed++;

	// Test 5: Parse custom color (purple)
	str = "255,0,225";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n\n", str);
	g_tests_total++;
	if (success && fabs(color.r - 1.0) < 0.001 && fabs(color.g - 0.0) < 0.001 && fabs(color.b - (225.0/255.0)) < 0.001)
		g_tests_passed++;

	// Test 6: Parse with whitespace
	str = "  128 ,  64 ,  192  ";
	original = str;
	success = parse_color(&str, &color);
	printf("Input: \"%s\"\n", original);
	printf("Success: %s\n", success ? "true" : "false");
	printf("Parsed color: ");
	print_color(color);
	printf("Remaining: \"%s\"\n", str);
	g_tests_total++;
	if (success && fabs(color.r - (128.0/255.0)) < 0.001 && fabs(color.g - (64.0/255.0)) < 0.001 && fabs(color.b - (192.0/255.0)) < 0.001)
		g_tests_passed++;

	print_separator();
}

static void	test_ambient_parsing(void)
{
	char	*str;
	double	ratio;
	t_color	color;

	printf("--- AMBIENT LIGHTING ---\n");
	str = "0.2 255,255,255";
	printf("Input: \"A %s\"\n", str);
	
	g_tests_total++;
	if (parse_double(&str, &ratio))
	{
		printf("✓ Ambient ratio: %.1f\n", ratio);
		if (parse_color(&str, &color))
		{
			printf("✓ Ambient color: ");
			print_color(color);
			g_tests_passed++;
		}
	}
	printf("\n");
}

static void	test_camera_parsing(void)
{
	char		*str;
	t_point		pos;
	t_vector	ornt;
	int			fov;

	printf("--- CAMERA ---\n");
	str = "-50,0,20 0,0,0 70";
	printf("Input: \"C %s\"\n", str);
	
	g_tests_total++;
	if (parse_point(&str, &pos))
	{
		printf("✓ Position: ");
		print_tuple(pos);
		if (parse_vector(&str, &ornt))
		{
			printf("✓ Orientation: ");
			print_tuple(ornt);
			if (parse_int(&str, &fov))
			{
				printf("✓ FOV: %d degrees (%.5f radians)\n", fov, fov * M_PI / 180.0);
				g_tests_passed++;
			}
		}
	}
	printf("\n");
}

static void	test_light_parsing(void)
{
	char		*str;
	t_point		pos;
	double		brightness;
	t_color		color;

	printf("--- LIGHT ---\n");
	str = "-40,0,30 0.7 255,255,255";
	printf("Input: \"L %s\"\n", str);
	
	g_tests_total++;
	if (parse_point(&str, &pos))
	{
		printf("✓ Position: ");
		print_tuple(pos);
		if (parse_double(&str, &brightness))
		{
			printf("✓ Brightness: %.1f\n", brightness);
			if (parse_color(&str, &color))
			{
				printf("✓ Color: ");
				print_color(color);
				printf("✓ Color * brightness: ");
				print_color(color_multiply(color, brightness));
				g_tests_passed++;
			}
		}
	}
	printf("\n");
}

static void	test_sphere_parsing(void)
{
	char		*str;
	t_point		center;
	double		diameter;
	t_color		color;

	printf("--- SPHERE ---\n");
	str = "0,0,20 20 255,0,0";
	printf("Input: \"sp %s\"\n", str);
	
	g_tests_total++;
	if (parse_point(&str, &center))
	{
		printf("✓ Center: ");
		print_tuple(center);
		if (parse_double(&str, &diameter))
		{
			printf("✓ Diameter: %.1f (radius: %.1f)\n", diameter, diameter / 2.0);
			if (parse_color(&str, &color))
			{
				printf("✓ Color: ");
				print_color(color);
				g_tests_passed++;
			}
		}
	}
	printf("\n");
}

static void	test_plane_parsing(void)
{
	char		*str;
	t_point		position;
	t_vector	normal;
	t_color		color;

	printf("--- PLANE ---\n");
	str = "0,0,0 0,1.0,0 255,0,225";
	printf("Input: \"pl %s\"\n", str);
	
	g_tests_total++;
	if (parse_point(&str, &position))
	{
		printf("✓ Position: ");
		print_tuple(position);
		if (parse_vector(&str, &normal))
		{
			printf("✓ Normal: ");
			print_tuple(normal);
			if (parse_color(&str, &color))
			{
				printf("✓ Color: ");
				print_color(color);
				g_tests_passed++;
			}
		}
	}
	printf("\n");
}

static void	test_cylinder_parsing(void)
{
	char		*str;
	t_point		position;
	t_vector	axis;
	double		diameter;
	double		height;
	t_color		color;

	printf("--- CYLINDER ---\n");
	str = "50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255";
	printf("Input: \"cy %s\"\n", str);
	
	g_tests_total++;
	if (parse_point(&str, &position))
	{
		printf("✓ Position: ");
		print_tuple(position);
		if (parse_vector(&str, &axis))
		{
			printf("✓ Axis: ");
			print_tuple(axis);
			if (parse_double(&str, &diameter))
			{
				printf("✓ Diameter: %.1f (radius: %.1f)\n", diameter, diameter / 2.0);
				if (parse_double(&str, &height))
				{
					printf("✓ Height: %.2f\n", height);
					if (parse_color(&str, &color))
					{
						printf("✓ Color: ");
						print_color(color);
						g_tests_passed++;
					}
				}
			}
		}
	}
	printf("\n");
}

static void	test_parse_complete_elements(void)
{
	printf("TEST: Parsing Complete .rt File Elements\n");
	printf("=========================================\n\n");

	test_ambient_parsing();
	test_camera_parsing();
	test_light_parsing();
	test_sphere_parsing();
	test_plane_parsing();
	test_cylinder_parsing();

	print_separator();
}

static void	test_edge_cases(void)
{
	char	*str;
	double	d;
	int		i;
	t_color	c;
	bool	success;

	printf("TEST: Edge Cases and Error Handling\n");
	printf("====================================\n\n");

	// Test 1: Color value out of range (too high)
	printf("--- Color value > 255 ---\n");
	str = "300,100,100";
	printf("Input: \"%s\"\n", str);
	success = parse_color(&str, &c);
	printf("Expected: false (value out of range)\n");
	printf("Result: %s\n\n", success ? "true" : "false");
	g_tests_total++;
	if (!success)
		g_tests_passed++;

	// Test 2: Color value out of range (negative)
	printf("--- Negative color value ---\n");
	str = "-10,100,100";
	printf("Input: \"%s\"\n", str);
	success = parse_color(&str, &c);
	printf("Expected: false (negative value)\n");
	printf("Result: %s\n\n", success ? "true" : "false");
	g_tests_total++;
	if (!success)
		g_tests_passed++;

	// Test 3: Ambient ratio > 1.0
	printf("--- Ambient ratio > 1.0 ---\n");
	str = "1.5";
	printf("Input: \"%s\"\n", str);
	success = parse_double(&str, &d);
	printf("Parsed: %s, Value: %.2f\n", success ? "true" : "false", d);
	printf("Note: Should be rejected by scene validation (0.0 - 1.0 range)\n\n");

	// Test 4: Negative diameter
	printf("--- Negative diameter ---\n");
	str = "-20.0";
	printf("Input: \"%s\"\n", str);
	success = parse_double(&str, &d);
	printf("Parsed: %s, Value: %.2f\n", success ? "true" : "false", d);
	printf("Note: Should be rejected by object validation (must be > 0)\n\n");

	// Test 5: FOV out of range
	printf("--- FOV = 200 (out of range) ---\n");
	str = "200";
	printf("Input: \"%s\"\n", str);
	success = parse_int(&str, &i);
	printf("Parsed: %s, Value: %d\n", success ? "true" : "false", i);
	printf("Note: Should be rejected by camera validation (0-180 range)\n\n");

	// Test 6: Missing component in vector
	printf("--- Incomplete vector (only 2 components) ---\n");
	str = "1.0,2.0";
	printf("Input: \"%s\"\n", str);
	printf("Note: parse_vector expects 3 components, will fail on third\n\n");

	print_separator();
}

void	test_parsing(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║                   PARSING TESTS                        ║\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("\n");

	test_parse_double();
	test_parse_int();
	test_parse_vector();
	test_parse_point();
	test_parse_color();
	test_parse_complete_elements();
	test_edge_cases();

	printf("\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║              PARSING TESTS COMPLETED                   ║\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("\n");
	if (g_tests_passed == g_tests_total)
		printf("✅ Tests passed: %d/%d\n\n", g_tests_passed, g_tests_total);
	else
		printf("⚠️  Tests passed: %d/%d\n\n", g_tests_passed, g_tests_total);
}


