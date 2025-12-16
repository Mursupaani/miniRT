/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:07:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/12/16 12:44:13 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	black;
t_color	white;

static void	test1()
{
	t_pattern	pattern;

	printf("TEST 1:\n");
	printf("Scenario: Creating a stripe pattern\n\
Given pattern ← stripe_pattern(white, black)\n\
Then pattern.a = white\n\
And pattern.b = black\n");
	pattern = stripe_pattern(white, black);
	print_pattern(pattern);
}

static void	test2()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 2:\n");
	printf("Scenario: A stripe pattern is constant in y\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0, 1, 0)) = white\n\
And stripe_at(pattern, point(0, 2, 0)) = white\n");
	pattern = stripe_pattern(white, black);
	printf("----------\n");
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 1, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 2, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

static void	test3()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 3:\n");
	printf("Scenario: A stripe pattern is constant in z\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0, 0, 1)) = white\n\
And stripe_at(pattern, point(0, 0, 2)) = white\n");
	pattern = stripe_pattern(white, black);
	printf("----------\n");
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 0, 1);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0, 0, 2);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

static void	test4()
{
	t_color		c;
	t_pattern	pattern;
	t_point		p;

	printf("TEST 4:\n");
	printf("Scenario: A stripe pattern alternates in x\n\
Given pattern ← stripe_pattern(white, black)\n\
Then stripe_at(pattern, point(0, 0, 0)) = white\n\
And stripe_at(pattern, point(0.9, 0, 0)) = white\n\
And stripe_at(pattern, point(1, 0, 0)) = black\n\
And stripe_at(pattern, point(-0.1, 0, 0)) = black\n\
And stripe_at(pattern, point(-1, 0, 0)) = black\n\
And stripe_at(pattern, point(-1.1, 0, 0)) = white\n");
	printf("----------\n");
	pattern = stripe_pattern(white, black);
	p = point(0, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(0.9, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-0.1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
	printf("----------\n");
	p = point(-1.1, 0, 0);
	c = stripe_at(pattern, p);
	print_tuple(p);
	print_color(c);
}

void	test_patterns(void)
{
	black = color(0, 0, 0);
	white = color(1, 1, 1);
	printf("\n");
	printf("------------- TESTING PATTERNS --------------\n");
	printf("_____________________________________________\n");
	test1();
	printf("_____________________________________________\n");
	test2();
	printf("_____________________________________________\n");
	test3();
	printf("_____________________________________________\n");
	test4();
	printf("_____________________________________________\n");
	printf("--------- TESTING PATTERNS FINISHED ---------\n");
	printf("\n");
}
