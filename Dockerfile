FROM morawskim/opensuse-42.3-kde5-devel

USER root

RUN zypper --non-interactive install krunner-devel ktextwidgets-devel \
  && zypper clean
  
RUN rpm --import https://repo.skype.com/rpm/stable/repodata/repomd.xml.key \
  && zypper --non-interactive ar https://repo.skype.com/rpm/stable/skype-stable.repo

RUN zypper --non-interactive install tmux skypeforlinux \
  && zypper clean
  
USER user
CMD ["startkde"]
