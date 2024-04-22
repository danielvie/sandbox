#pragma once

template <typename T>
concept animal_like = requires(T t) { t.wag_tail(); };

// template <typename T>
// concept cat_like = requires(T t){ t.meow(); };

template <typename T>
concept cat_like = animal_like<T> && requires(T t){ t.meow(); };

template <typename T>
concept dog_like = animal_like<T> && requires(T t){ t.bark(); };

template <typename T>
concept bird_like = animal_like<T> && requires(T t){ t.flap_wings(); };

template <typename T>
concept strange_thing_like = dog_like<T> && bird_like<T>;