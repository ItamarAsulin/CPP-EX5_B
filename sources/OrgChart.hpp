//
// Created by itamarq on 5/15/22.
//

#ifndef EX5_A_ORGCHART_HPP
#define EX5_A_ORGCHART_HPP

#include "CharIterator.hpp"

using namespace std;
namespace ariel {

    class OrgChart {
    private:
        Node *head;
        Node *iterationNode;

        void free();

        void validateRoot();

        void updateNodesForLevelOrder();

        void updateNodesForReverseLevelOrder();

        void updateNodesForPreorder();

    public:
        OrgChart();

        OrgChart(OrgChart &other);

        OrgChart(OrgChart &&other) = default;

        OrgChart &operator=(OrgChart &&) = default;

        OrgChart &operator=(const OrgChart &other) = default;

        ~OrgChart();

        OrgChart &add_sub(const string &superiorName, const string &subordinateName);

        OrgChart &add_root(const string &rootName);

        Node *
        getSuperior(const string &superiorName);

        Node *getHead();


        /**
         * iteration functions
         */
        // general OrgChart begin and end
        ChartIterator begin();

        ChartIterator end();

        // level order begin and end
        ChartIterator begin_level_order();

        ChartIterator end_level_order();

        // reverse level order begin and end
        ChartIterator begin_reverse_order();

        ChartIterator reverse_order();

        // preorder begin and end
        ChartIterator begin_preorder();

        ChartIterator end_preorder();

        friend std::ostream &operator<<(std::ostream &output, const OrgChart &chart);

    };

    /**
     * validation functions.
     */
    void validateName(const string &name);


}
#endif //EX5_A_ORGCHART_HPP
