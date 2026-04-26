/*
** EPITECH PROJECT, 2026
** map
** File description:
** criterion tests for all map methods
*/

#include <criterion/criterion.h>
#include <stdint.h>
#include "map.h"

// helpers

static map_t make_int_map(void)
{
    return init_map(sizeof(int));
}

static void insert_int(map_t *m, const char *key, int val)
{
    map_insert(m, key, &val);
}

static int get_int(const map_t *m, const char *key)
{
    return *(int *)map_at(m, key);
}

static int cmp_gt_five(const char *key, const void *value)
{
    (void)key;
    return *(const int *)value > 5;
}

static int cmp_never(const char *key, const void *value)
{
    (void)key;
    (void)value;
    return 0;
}

// tests

Test(init_map, zero_size)
{
    map_t m = make_int_map();
    cr_assert_eq(map_size(&m), 0);
    map_clear(&m);
}

Test(init_map, bucket_count)
{
    map_t m = make_int_map();
    cr_assert_eq(m.bucket_count, MAP_BUCKET_COUNT);
    map_clear(&m);
}

Test(init_map, child_size_stored)
{
    map_t m = init_map(sizeof(double));
    cr_assert_eq(m.child_size, sizeof(double));
    map_clear(&m);
}

Test(map_insert, single_entry_returns_zero)
{
    map_t m = make_int_map();
    int v = 42;
    cr_assert_eq(map_insert(&m, "foo", &v), 0);
    map_clear(&m);
}

Test(map_insert, single_entry_increases_size)
{
    map_t m = make_int_map();
    insert_int(&m, "foo", 1);
    cr_assert_eq(map_size(&m), 1);
    map_clear(&m);
}

Test(map_insert, multiple_entries_size)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    insert_int(&m, "b", 2);
    insert_int(&m, "c", 3);
    cr_assert_eq(map_size(&m), 3);
    map_clear(&m);
}

Test(map_insert, duplicate_key_updates_value)
{
    map_t m = make_int_map();
    insert_int(&m, "x", 10);
    insert_int(&m, "x", 99);
    cr_assert_eq(map_size(&m), 1);
    cr_assert_eq(get_int(&m, "x"), 99);
    map_clear(&m);
}

Test(map_at, existing_key)
{
    map_t m = make_int_map();
    insert_int(&m, "hello", 7);
    cr_assert_not_null(map_at(&m, "hello"));
    cr_assert_eq(get_int(&m, "hello"), 7);
    map_clear(&m);
}

Test(map_at, missing_key_returns_null)
{
    map_t m = make_int_map();
    insert_int(&m, "hello", 7);
    cr_assert_null(map_at(&m, "world"));
    map_clear(&m);
}

Test(map_at, value_after_update)
{
    map_t m = make_int_map();
    insert_int(&m, "k", 1);
    insert_int(&m, "k", 2);
    cr_assert_eq(get_int(&m, "k"), 2);
    map_clear(&m);
}

Test(map_erase, erase_first_entry)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    cr_assert_eq(map_erase(&m, 0), 0);
    cr_assert_eq(map_size(&m), 0);
    map_clear(&m);
}

Test(map_erase, erase_decrements_size)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    insert_int(&m, "b", 2);
    map_erase(&m, 0);
    cr_assert_eq(map_size(&m), 1);
    map_clear(&m);
}

Test(map_erase, erase_out_of_bounds_returns_minus_one)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    cr_assert_eq(map_erase(&m, 5), -1);
    map_clear(&m);
}

Test(map_erase, erase_on_empty_map)
{
    map_t m = make_int_map();
    cr_assert_eq(map_erase(&m, 0), -1);
    map_clear(&m);
}

Test(map_size, empty_map)
{
    map_t m = make_int_map();
    cr_assert_eq(map_size(&m), 0);
    map_clear(&m);
}

Test(map_size, after_insertions)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    insert_int(&m, "b", 2);
    cr_assert_eq(map_size(&m), 2);
    map_clear(&m);
}

Test(map_empty, initially_empty)
{
    map_t m = make_int_map();
    cr_assert(map_empty(&m));
    map_clear(&m);
}

Test(map_empty, not_empty_after_insert)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    cr_assert_not(map_empty(&m));
    map_clear(&m);
}

Test(map_empty, empty_after_erase)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    map_erase(&m, 0);
    cr_assert(map_empty(&m));
    map_clear(&m);
}

Test(map_max_size, returns_positive)
{
    map_t m = make_int_map();
    cr_assert_gt(map_max_size(&m), 0);
    map_clear(&m);
}

Test(map_max_size, consistent_with_size_max)
{
    map_t m = make_int_map();
    cr_assert_eq(map_max_size(&m), SIZE_MAX / sizeof(map_entry_t));
    map_clear(&m);
}

Test(map_swap, sizes_are_exchanged)
{
    map_t a = make_int_map();
    map_t b = make_int_map();
    insert_int(&a, "x", 1);
    insert_int(&a, "y", 2);
    insert_int(&b, "z", 3);
    map_swap(&a, &b);
    cr_assert_eq(map_size(&a), 1);
    cr_assert_eq(map_size(&b), 2);
    map_clear(&a);
    map_clear(&b);
}

Test(map_swap, values_follow_maps)
{
    map_t a = make_int_map();
    map_t b = make_int_map();
    insert_int(&a, "k", 10);
    insert_int(&b, "k", 20);
    map_swap(&a, &b);
    cr_assert_eq(get_int(&a, "k"), 20);
    cr_assert_eq(get_int(&b, "k"), 10);
    map_clear(&a);
    map_clear(&b);
}

Test(map_merge, copies_all_entries)
{
    map_t dst = make_int_map();
    map_t src = make_int_map();
    insert_int(&src, "a", 1);
    insert_int(&src, "b", 2);
    map_merge(&dst, &src);
    cr_assert_eq(map_size(&dst), 2);
    map_clear(&dst);
    map_clear(&src);
}

Test(map_merge, src_key_overwrites_dst)
{
    map_t dst = make_int_map();
    map_t src = make_int_map();
    insert_int(&dst, "k", 1);
    insert_int(&src, "k", 99);
    map_merge(&dst, &src);
    cr_assert_eq(get_int(&dst, "k"), 99);
    cr_assert_eq(map_size(&dst), 1);
    map_clear(&dst);
    map_clear(&src);
}

Test(map_merge, src_unchanged)
{
    map_t dst = make_int_map();
    map_t src = make_int_map();
    insert_int(&src, "a", 1);
    map_merge(&dst, &src);
    cr_assert_eq(map_size(&src), 1);
    map_clear(&dst);
    map_clear(&src);
}

Test(map_find, finds_matching_entry)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 3);
    insert_int(&m, "b", 8);
    void *result = map_find(&m, cmp_gt_five);
    cr_assert_not_null(result);
    cr_assert_eq(*(int *)result, 8);
    map_clear(&m);
}

Test(map_find, returns_null_when_no_match)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    insert_int(&m, "b", 2);
    cr_assert_null(map_find(&m, cmp_gt_five));
    map_clear(&m);
}

Test(map_find, empty_map_returns_null)
{
    map_t m = make_int_map();
    cr_assert_null(map_find(&m, cmp_never));
    map_clear(&m);
}

Test(map_count, counts_matching_entries)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 10);
    insert_int(&m, "b", 2);
    insert_int(&m, "c", 7);
    cr_assert_eq(map_count(&m, cmp_gt_five), 2);
    map_clear(&m);
}

Test(map_count, zero_when_no_match)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    cr_assert_eq(map_count(&m, cmp_gt_five), 0);
    map_clear(&m);
}

Test(map_count, zero_on_empty_map)
{
    map_t m = make_int_map();
    cr_assert_eq(map_count(&m, cmp_gt_five), 0);
    map_clear(&m);
}

Test(map_count, all_match)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 6);
    insert_int(&m, "b", 7);
    insert_int(&m, "c", 8);
    cr_assert_eq(map_count(&m, cmp_gt_five), 3);
    map_clear(&m);
}

Test(map_clear, size_becomes_zero)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    insert_int(&m, "b", 2);
    map_clear(&m);
    cr_assert_eq(map_size(&m), 0);
    map_clear(&m);
}

Test(map_clear, map_is_empty_after)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    map_clear(&m);
    cr_assert(map_empty(&m));
    map_clear(&m);
}

Test(map_clear, at_returns_null_after)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    map_clear(&m);
    cr_assert_null(map_at(&m, "a"));
    map_clear(&m);
}

Test(map_clear, double_clear_is_safe)
{
    map_t m = make_int_map();
    insert_int(&m, "a", 1);
    map_clear(&m);
    map_clear(&m);
    cr_assert_eq(map_size(&m), 0);
}
