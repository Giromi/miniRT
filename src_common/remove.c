#include "vector.h"
#include "my_func.h"
#include "minirt.h"

void debugPrintVec(char *str, t_vector *vector)
{
	printf("%s : x = %lf ",  str, vector->x);
	printf("%s : y = %lf ",  str, vector->y);
	printf("%s : z = %lf\n", str, vector->z);
}

void debugPrintDouble(char *str1, char *str2, double a, double b)
{
	printf("%s = %lf ",  str1, a);
	printf("%s = %lf\n", str2, b);
}

void	print_cam(t_camera *cam) // 지워야함
{
	t_camera	*curr;

	curr = cam;
	printf("==========print_cam start==========\n");
	while (curr)
	{
		printf("-------CAM------\n");
		printf("orign x : %lf ", (curr->orig.x));
		printf("orign y : %lf ", (curr->orig.y));
		printf("orign z : %lf \n", (curr->orig.z));
		printf("viewport_w : %lf \n", (curr->viewport[0]));
		printf("viewport_h : %lf \n", (curr->viewport[1]));
		printf("normal x : %lf ", curr->normal.x);
		printf("normal y : %lf ", curr->normal.y);
		printf("normal z : %lf \n", curr->normal.z);
		if (curr->next == cam)
			break ;
		curr = curr->next;
	}
	printf("==========print_cam end==========\n");
}


void	print_obj(t_object *obj) // 지워야함
{
	t_object	*curr;

	curr = obj;
	printf("==========print_obj start==========\n");
	while (curr)
	{
		if (curr->type == SP)
		{
			printf("-------type SP------\n");
			printf("x : %lf ", ((t_sphere *)curr->elem)->center.x);
			printf("y : %lf ", ((t_sphere *)curr->elem)->center.y);
			printf("z : %lf \n", ((t_sphere *)curr->elem)->center.z);
			printf("radius : %lf \n", ((t_sphere *)curr->elem)->radius);
			printf("color  R : %lf ", curr->albedo.x);
			printf("color  G : %lf ", curr->albedo.y);
			printf("color  B : %lf \n", curr->albedo.z);
		}
		else if (curr->type == PL)
		{
			printf("-------type PL------\n");
			printf("x : %lf ", ((t_plane *)curr->elem)->center.x);
			printf("y : %lf ", ((t_plane *)curr->elem)->center.y);
			printf("z : %lf \n", ((t_plane *)curr->elem)->center.z);
			printf("normal x : %lf ", ((t_plane *)curr->elem)->normal.x);
			printf("normal y : %lf ", ((t_plane *)curr->elem)->normal.y);
			printf("normal z : %lf \n", ((t_plane *)curr->elem)->normal.z);
			printf("color  R : %lf ", curr->albedo.x);
			printf("color  G : %lf ", curr->albedo.y);
			printf("color  B : %lf \n", curr->albedo.z);
		}
		else if (curr->type == CP)
		{
			printf("-------type CP------\n");
			printf("x : %lf ", ((t_plane *)curr->elem)->center.x);
			printf("y : %lf ", ((t_plane *)curr->elem)->center.y);
			printf("z : %lf \n", ((t_plane *)curr->elem)->center.z);
			printf("normal x : %lf ", ((t_plane *)curr->elem)->normal.x);
			printf("normal y : %lf ", ((t_plane *)curr->elem)->normal.y);
			printf("normal z : %lf \n", ((t_plane *)curr->elem)->normal.z);
			printf("color  R : %lf ", curr->albedo.x);
			printf("color  G : %lf ", curr->albedo.y);
			printf("color  B : %lf \n", curr->albedo.z);
		}

		else if (curr->type == CY)
		{
			printf("-------type CY------\n");
			printf("x : %lf ", ((t_conlinder *)curr->elem)->center.x);
			printf("y : %lf ", ((t_conlinder *)curr->elem)->center.y);
			printf("z : %lf \n", ((t_conlinder *)curr->elem)->center.z);
			printf("normal x : %lf ", ((t_conlinder *)curr->elem)->normal.x);
			printf("normal y : %lf ", ((t_conlinder *)curr->elem)->normal.y);
			printf("normal z : %lf \n", ((t_conlinder *)curr->elem)->normal.z);
			printf("radius : %lf \n", ((t_conlinder *)curr->elem)->radius);
			printf("height : %lf \n", ((t_conlinder *)curr->elem)->height);
			printf("color  R : %lf ", curr->albedo.x);
			printf("color  G : %lf ", curr->albedo.y);
			printf("color  B : %lf \n", curr->albedo.z);
		}
		curr = curr->next;
	}
	printf("==========print_obj end==========\n");
}

void	ae()
{
	system("leaks miniRT");
}
