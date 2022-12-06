#include "pch.h"

#include "SearchMetrics.h"

#include "Global.h"

namespace
{
    const std::string MetricsOutputFile("C:\\Users\\angus\\OneDrive\\Desktop\\Code\\ChessEngine\\x64\\Release\\SearchMetrics.csv");
}

namespace ChessEngine
{
    void SearchMetrics::PrintMetrics() const
    {
        std::stringstream ss;

        ss  << "Searching (Max Depth = " << static_cast<unsigned int>(m_maxDepth) << ")" << "\n"
            << "==========================" << "\n"
            << "    Total searched positions: " << m_searchTotalPositions << "\n"
            << "    Total time searching: " << m_searchTotalTime.count() << " seconds" << "\n"
            << "\n"
            << "Generation" << "\n"
            << "==========" << "\n"
            << "    Total generated positions: " << m_generationTotalPositions << "\n"
            << "    Total time generating: " << m_generationTotalTime.count() << " seconds" << "\n"
            << "\n"
            << "Evaluation" << "\n"
            << "==========" << "\n"
            << "    Total evaluated positions: " << m_evaluationTotalPositions << "\n"
            << "    Total time evaluating: " << m_evaluationTotalTime.count() << " seconds" << "\n"
            << "\n";

        std::cout << ss.str();
        std::cout.flush();
    }

    void WriteHeaders(std::ofstream& fs)
    {
        fs  << "Version,"
            << "Max Depth,"
            << "Total Search Positions,"
            << "Total Time Searching,"
            << "Total Generated Positions,"
            << "Total Time Generating,"
            << "Total Evaluated Positions,"
            << "Total Time Evaluating,"
            << std::endl;
    }

    void SearchMetrics::WriteMetrics() const
    {
        std::ofstream fs;

        try
        {
            if (!std::filesystem::exists(MetricsOutputFile))
            {
                fs.open(MetricsOutputFile);
                WriteHeaders(fs);
            }
            else
            {
                fs.open(MetricsOutputFile, std::ofstream::app);
            }
        }
        catch (...)
        {
            std::cerr << "Something went wrong writing metrics to CSV" << std::endl;
        }

        fs  << Version << ","
            << static_cast<unsigned int>(m_maxDepth) << ","
            << m_searchTotalPositions << ","
            << m_searchTotalTime.count() << ","
            << m_generationTotalPositions << ","
            << m_generationTotalTime.count() << ","
            << m_evaluationTotalPositions << ","
            << m_evaluationTotalTime.count() << ","
            << "\n";

        fs.flush();
        fs.close();
    }
}