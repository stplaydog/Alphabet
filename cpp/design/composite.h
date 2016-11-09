#ifndef COMPOSITE_H_
#define COMPOSITE_H_
#include <vector>
#include <algorithm>
/*
 * This library provide a reusable C++ template class which can be easily re used -
 * in place of implementing Composite design pattern.
 * Composite design pattern is one among the 23 popular design patterns -
 * identified by Gang of Four (GoF).
 * In a Composite pattern there will  be three type of classes like, component, 
 * composite and leaf.
 * Composite and leaf are derived from Component. Composite is a container class -
 * which can store many other Components.
 */
namespace GoFPatterns
{
    using namespace std;
    /*
     * This template class automatically inherits itself from the given Component type
     * and in addition it provides the containment features to the expanded template type.
     */
    template<typename Component>
        class Composite: public Component
    {
        protected:
            vector<Component*> children; //Child components list.
        public:
            /*
             * An iterator type is defined which can be used from Composite class
             * To perform extensive operations on the Children list like Insert, Search etc.
             * This is provided just for Ease of use for Composite class developers.
             */
            typedef typename vector<Component*>::iterator ChildIterator;
            /*
             * Add a Component to the child list.
             * Check to avoid duplication of same child in the list.
             */
            void AddChild(Component* child)
            {
                ChildIterator itr = find(children.begin(),children.end(),child);
                if( itr == children.end())
                {
                    children.push_back(child);
                }
            }
            /*
             * Remove a component from the child list if it exist there.
             */
            void RemoveChild(Component* child)
            {
                ChildIterator itr = find(children.begin(),children.end(),child);
                if( itr != children.end())
                {
                    children.erase(itr);
                }
            }
            /*
             * Remove all child from the list.
             */
            void Clear()
            {
                children.clear();
            }
            virtual ~Composite()
            {

            }
    }; //End class Composite
}//End name space GoFPatterns
#endif /* COMPOSITE_H_ */ 
