INHERIT += "sstate-reuse"

# We know RHEL 5 is the oldest distro we support, and that binaries built
# there will run on any other host we support
SSTATE_MIRROR_HOSTS = "RedHatEnterprise-5"

def lsb_adjust_hook(distro_id, ver):
    """This hook ensures that RHEL server, RHEL client, and CentOS all return
    'RedHatEnterprise' for distro, and '5' for the version, as we know minor
    versions for these distros are compatible, and these distros are
    compatible with one another."""

    if distro_id in ('RedHatEnterpriseClient', 'RedHatEnterpriseServer',
                     'CentOS'):
        distro_id = 'RedHatEnterprise'

        try:
            major_ver, _ = ver.split('.', 1)
        except ValueError:
            pass
        else:
            ver = major_ver
    return distro_id, ver

LSB_DISTRO_ADJUST = "lsb_adjust_hook"