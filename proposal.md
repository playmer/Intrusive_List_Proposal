# Proposal for std::intrusive_list #
This proposal suggests the creation of a std::intrusive_list in C++.

##Pre-existing implementations
There exist several implementations of various intrusive containers to work from to create the interface for a std::intrusive_list. These serve as both an inspiration as well as the impetus to create this proposal. Several of the groups that make up SG14 have their own needs with this container and so it will be with much care that we look upon both the following implementations as well as references to determine what would be best to put forth to standardize.

 * [Boost.Intrusive](https://github.com/boostorg/intrusive/blob/develop/include/boost/intrusive/list.hpp)
 * [Folly (This simply contains minor conveniences for Boost.Intrusive)](
 https://github.com/facebook/folly/blob/master/folly/IntrusiveList.h)
 * [EASTL](https://github.com/electronicarts/EASTL/blob/master/include/EASTL/intrusive_list.h)
 * [Coho](https://github.com/webcoyote/coho/blob/master/Base/List.h)

##References
 * [In-Depth: Intrusive Lists, John McCutchan. 2011](http://www.gamasutra.com/view/news/128568/InDepth_Intrusive_Lists.php)
 * [Avoiding game crashes related to linked lists, Patrick Wyatt. 2012](http://www.codeofhonor.com/blog/avoiding-game-crashes-related-to-linked-lists)
 * [C++ Hybrid Intrusive Lists, Henrique Bucher. 2016](https://www.linkedin.com/pulse/optimizing-cache-scheduler-henrique-bucher)

##Open Questions
 1. ###Does std::intrusive_list enforce ownership?
    It seems that it would be hurtful to force items inside of an intrusive_list to be owned by said list. One of the merits of intrusive containers is that it can be easy to allow it to be non-owning.
    
    Perhaps one option is an owning intrusive_list as well as a non-owning intrusive_list. This could be activated similarly to modes in the Boost implementation. A safe_mode that asserts upon certain "bad" states (destructing when still in a list, adding to a list while still in a list). A auto_detach mode that detacthes upon destruction. Finally a owning_mode where the objects *are* copies allocated by the allocator.
 2. ###Is it possible for objects to be in multiple lists?
    Patrick Wyatt suggests having the user manually store the nodes within their objects and using the offsetof keyword to detect where the nodes lay. This solution works, but is cumbersome for the user. Without attempting to  implement both, this may make it difficult, though not impossible to implement question 4. Boost allows a similar method to Patricks through the use of member_hook classes that function as nodes in a member form. Our implementation follows Boosts lead in this regard.
 3. ###Do objects inside an std::intrusive_list remove themselves from that list when they are destructed?
    Our proposed implementation does this, but this interferes with question 4. This appears at first glance to be a strict benefit of intrusive lists. The objects are explicitly the nodes within the list, and they have pointers to both the previous and next nodes, so it's trivial to implement them removing themselves, barring multithreaded code as mentioned by Patrick Wyatt. Boost.Intrusive leaves this as an option for the user by allowing them to specify a mode: auto_detach. 
    
    As mentioned this can also cause issues with question 4, as just because the object removes itself doesn't mean that duplicate nodes would as well. This could possibly be mitigated by caching the duplicate nodes and checking them upon the destruction of another node, but it increases the algorithmic complexity and defeats the purpose of the container in the first place.
 4. ###Is there a way for a std::intrusive_list to be populated with the same object multiple times?
    This is in reference to the "Hybrid Intrusive Lists" as brought up by Henrique Butcher. Henrique's solution to this is clever, simply create a node whose node pointer doesn't equal itself. However this causes issues as 