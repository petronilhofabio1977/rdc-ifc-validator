#include "ProjectSummary.hpp"
#include "ActionReport.hpp"

void update_project_summary(
    ProjectSummary& summary,
    const ActionReport& report
) {
    summary.total++;

    bool has_critical = false;
    bool has_alerts = false;

    for (const auto& s : report.summary) {
        if (s.severity == Severity::CRITICAL) {
            has_critical = true;
        } else {
            has_alerts = true;
            summary.alert_count[s.code]++;
        }
    }

    if (has_critical) {
        summary.rejected++;
    } else if (has_alerts) {
        summary.approved_with_alerts++;
    } else {
        summary.approved++;
    }
}
