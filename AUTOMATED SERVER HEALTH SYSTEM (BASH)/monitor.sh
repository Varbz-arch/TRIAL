#!/bin/bash
# =====================================================
# monitor.sh - Simple Linux Server Health Monitor
# Checks CPU, RAM, Disk usage and failed SSH logins.
# Logs results and sends a Telegram alert if thresholds
# are crossed.
# =====================================================

# ---------- CONFIG ----------
CPU_THRESHOLD=80        # percent
RAM_THRESHOLD=80        # percent
DISK_THRESHOLD=80       # percent
LOGIN_FAIL_THRESHOLD=5  # failed SSH attempts

LOG_DIR="$HOME/monitor_logs"
LOG_FILE="$LOG_DIR/health_$(date +%F).log"

# Telegram (optional - leave blank to disable alerts)
TELEGRAM_BOT_TOKEN=""
TELEGRAM_CHAT_ID=""

mkdir -p "$LOG_DIR"

# ---------- FUNCTIONS ----------

get_cpu_usage() {
    # 100 - idle%
    top -bn1 | grep "Cpu(s)" | awk '{print 100 - $8}' | cut -d. -f1
}

get_ram_usage() {
    free | awk '/Mem:/ {printf "%.0f", $3/$2 * 100}'
}

get_disk_usage() {
    df -h / | awk 'NR==2 {print $5}' | tr -d '%'
}

get_failed_logins() {
    if [ -f /var/log/auth.log ]; then
        grep "Failed password" /var/log/auth.log 2>/dev/null | wc -l
    else
        echo 0
    fi
}

get_top_processes() {
    ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -6
}

send_telegram_alert() {
    local message="$1"
    if [ -n "$TELEGRAM_BOT_TOKEN" ] && [ -n "$TELEGRAM_CHAT_ID" ]; then
        curl -s -X POST "https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage" \
            -d chat_id="${TELEGRAM_CHAT_ID}" \
            -d text="${message}" > /dev/null
    fi
}

log() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') | $1" | tee -a "$LOG_FILE"
}

# ---------- MAIN ----------

CPU=$(get_cpu_usage)
RAM=$(get_ram_usage)
DISK=$(get_disk_usage)
FAILED_LOGINS=$(get_failed_logins)

log "CPU: ${CPU}% | RAM: ${RAM}% | DISK: ${DISK}% | Failed SSH logins: ${FAILED_LOGINS}"

ALERT_MSG=""

if [ "$CPU" -ge "$CPU_THRESHOLD" ]; then
    ALERT_MSG+="⚠️ High CPU usage: ${CPU}%\n"
fi

if [ "$RAM" -ge "$RAM_THRESHOLD" ]; then
    ALERT_MSG+="⚠️ High RAM usage: ${RAM}%\n"
fi

if [ "$DISK" -ge "$DISK_THRESHOLD" ]; then
    ALERT_MSG+="⚠️ High Disk usage: ${DISK}%\n"
fi

if [ "$FAILED_LOGINS" -ge "$LOGIN_FAIL_THRESHOLD" ]; then
    ALERT_MSG+="🚨 ${FAILED_LOGINS} failed SSH login attempts detected!\n"
fi

if [ -n "$ALERT_MSG" ]; then
    log "ALERT TRIGGERED:"
    log "$(get_top_processes)"
    echo -e "$ALERT_MSG" | tee -a "$LOG_FILE"
    send_telegram_alert "Server Alert on $(hostname):\n${ALERT_MSG}"
else
    log "All systems normal."
fi