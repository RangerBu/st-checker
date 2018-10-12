find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message("Find boost")
else()
    message("Need boost")
endif()

SET(WALI_SRC
        Reach.cpp
        StringSource.cpp
        Common.cpp
        SemElemPair.cpp
        KeySpace.cpp
        KeySetSource.cpp
        TotalOrderWorklist.cpp
        KeyOrderWorklist.cpp
        RankedWorklist.cpp
        ShortestPathWorklist.cpp
        SemElem.cpp
        SemElemTensor.cpp
        Exception.cpp
        Printable.cpp
        Key.cpp
        IntSource.cpp
        Markable.cpp
        WeightFactory.cpp
        KeyPairSource.cpp
        IMergeFn.cpp
        MergeFn.cpp
        MergeFnFactory.cpp
        ShortestPathSemiring.cpp
        LongestSaturatingPathSemiring.cpp
        domains/SemElemSet.cpp
        domains/RepresentativeString.cpp
        wpds/RuleFunctor.cpp
        wpds/Config.cpp
        wpds/ewpds/ERule.cpp
        wpds/ewpds/ETrans.cpp
        wpds/ewpds/EWPDS.cpp
        wpds/Rule.cpp
        wpds/fwpds/FWPDS.cpp
        wpds/fwpds/SWPDS.cpp
        wpds/fwpds/LazyTrans.cpp
        wpds/Wrapper.cpp
        wpds/DebugWPDS.cpp
        wpds/WPDS.cpp
        wpds/GenKeySource.cpp
        wfa/State.cpp
        wfa/WFA.cpp
        wfa/WFA-eclose.cpp
        wfa/WFA-path_summary.cpp
        wfa/ITrans.cpp
        wfa/Trans.cpp
        wfa/WeightMaker.cpp
        wfa/TransFunctor.cpp
        wfa/TransSet.cpp
        wfa/DeterminizeWeightGen.cpp
        wfa/epr/EPA.cpp
        wfa/epr/FunctionalWeight.cpp
        wfa/epr/FunctionalWeightMaker.cpp
        witness/WitnessExtend.cpp
        witness/WitnessWrapper.cpp
        witness/WitnessRule.cpp
        witness/Visitor.cpp
        witness/CalculatingVisitor.cpp
        witness/WitnessMergeFn.cpp
        witness/VisitorDot.cpp
        witness/WitnessTrans.cpp
        witness/VisitorPrinter.cpp
        witness/Witness.cpp
        witness/WitnessCombine.cpp
        witness/WitnessMerge.cpp
        witness/WitnessLengthWorklist.cpp
        graph/RegExp.cpp
        graph/LinkEval.cpp
        regex/Concat.cpp
        regex/Regex.cpp
        regex/Root.cpp
        regex/Star.cpp
        regex/Union.cpp
        util/StringUtils.cpp
        util/ParseArgv.cpp
        util/Timer.cpp
        util/details/Partition.cpp
        graph/Functional.cpp
        graph/Graph.cpp
        graph/IntraGraph.cpp
        graph/InterGraph.cpp
        graph/SummaryGraph.cpp
        )
add_library(wali SHARED ${WALI_SRC})
#add_library(wali ${WALI_SRC})

target_link_libraries(wali ${Boost_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})